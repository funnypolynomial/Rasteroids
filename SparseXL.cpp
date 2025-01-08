#include <Arduino.h>
#include "Game.h"
#include "SparseXL.h"

namespace SparseXL {
/*
  Sparse pixels! The key to making this work on an Arduino (with only 2k RAM).

 
  sparseXL
  This extension to the original algorithm ("sparse-B", for ElitePetite) allows columns greater than 255.
  A run is encoded as 1, 2, 3 or 4 bytes.  
  The first byte is the start column.
  0: If the first byte is ESC (0xFF), skip over it. The column is the new first byte, plus 255.
  1: If the next byte is greater than the column, or the first byte is the last in a row block, this is a 1-byte representation and the run length is 1.
    (the next byte is actually the first byte in another run)
  2: If the next byte is less than or equal to the column, this is a 2-byte representation and that next byte is the run length.
  3: If the next byte is NUL (0x00) this is a 3-byte representation and the run length is the next+1 byte.
  Note: Run lengths are limited to 255 pixels. Potentially this could be solved with another "escape" encoding.
   

  Consider this triangle and line:
  col 012345678901234567890
    0|      ***
    1|     *   ***
    2|    *       ***
    3|   *           ***
    4|  *      ******
    5| ********
    6|                        ...           ***
                              ... column 300^

  SparseXL would encode this as:
    rows  pool bytes
    [2]   {6,3},
    [3]          {5}, {9,3},
    [3]                      {4}, {12,3},
    [3]                                   {3}, {15,3},
    [3]                                                {2}, {9,6},
    [2]                                                            {1,0,8},
    [3]                                                                     {255,45,3}
*/

// Special values
#define INF 0x7FFF
#define NUL 0x00
#define ESC 0xFF

// Drawn in full
#define PAINT_WINDOW_ORIGIN_X 0
#define PAINT_WINDOW_ORIGIN_Y 0
const int SPARSE_ROWS = SCREEN_HEIGHT;
const int SPARSE_COLS = SCREEN_WIDTH;

const int SPARSE_POOL_SIZE = 1000;

// the x at _ptr in the pool
#define SPARSE_GET_X(_ptr)      (*_ptr)
// the number of pixels in the run at _ptr in the pool
#define SPARSE_GET_LEN(_last, _ptr)    (((_last) || *_ptr < *(_ptr+1)) ? 1 : ((*(_ptr+1) == NUL) ? *(_ptr+2) : *(_ptr+1)))
// number of bytes in the entry at _ptr in the pool
#define SPARSE_GET_SIZE(_last, _ptr)   (((_last) || *_ptr < *(_ptr+1)) ? 1 : ((*(_ptr+1) == NUL) ? 3 : 2))

byte rows[SPARSE_ROWS]; // number of bytes in row's sparse representation
byte pool[SPARSE_POOL_SIZE]; // representations go here ("values", "cols"!)
uint16_t pool_top;    // index to next free byte
byte* cachePtr = NULL;
int16_t cacheY = INF; 
int16_t cacheX = INF;
bool cacheLast = false;
const int numMidRows = 4;
uint16_t sumToMidRow[numMidRows]; // cache the sum of the rows up to n*SPARSE_ROWS/numMidRows
uint16_t highWater = 0;
uint16_t rowOffset = 0;
bool full = false;
#ifdef DEBUG  
#define SET_HIGHWATER(_rhs) highWater = _rhs
#else
#define SET_HIGHWATER(_rhs)
#endif

static bool Insert(int16_t y, byte* pValue, byte value, byte value2 = 0)
{
  // inserts a new byte *at* pValue. Bytes above are shuffled
  // does most of the work, shuffles up the pool to make room for the new value
  // true if there was room
  // Also handles two bytes, if value2 != 0

  if (value2)
  {
    // special case, insert NUL & 2
    if (pool_top < SPARSE_POOL_SIZE - 1)
    {
      if (rows[y] > 253)
      {
        full = true;
        return false;
      }
      // there's room for 2 bytes
      // shuffle pool bytes up
      memmove(pValue + 2, pValue, (pool + pool_top) - pValue);
      *pValue = value;
      *(pValue + 1) = value2;
      pool_top += 2;
      rows[y] += 2;
      for (int midRow = 1; midRow < numMidRows; midRow++)
        if (y < midRow*SPARSE_ROWS/numMidRows)
          sumToMidRow[midRow] += 2;
      SET_HIGHWATER(max(highWater, pool_top));
      return true;
    }
  }
  else if (pool_top < SPARSE_POOL_SIZE)
  {
    if (rows[y] > 254)
    {
      full = true;
      return false;
    }
    // there's room
    // shuffle pool bytes up
    memmove(pValue + 1, pValue, (pool + pool_top) - pValue);
    *pValue = value;
    pool_top++;
    rows[y]++;
    for (int midRow = 1; midRow < numMidRows; midRow++)
      if (y < midRow*SPARSE_ROWS/numMidRows)
        sumToMidRow[midRow]++;
    SET_HIGHWATER(max(highWater, pool_top));
    return true;
  }
  SET_HIGHWATER(SPARSE_POOL_SIZE);
  full = true;
  return false;
}

int dbgY = 999;
int dbgY2 = 999;
static void Pixel(int16_t x, int16_t y)
{
  // set the pixel in the sparse data
  y -= rowOffset;
  if (y >= SPARSE_ROWS || x >= SPARSE_COLS || x < 0 || y < 0)
    return;

  if (cacheY == y && cacheX == x)
  {
    // cache the last location to quickly append to horizontal sequences
    byte* thisPtr = cachePtr;
    byte bytes = SPARSE_GET_SIZE(cacheLast, thisPtr);
    x = SPARSE_GET_X(thisPtr);
    cacheLast = false;
    if (bytes == 1)
    {
      if (x >= 2) // 2 bytes will work
      {
        if (!Insert(y, thisPtr + 1, 2))  // len=2
          cacheY = INF;
      }
      else // need 3
      {
        if (!Insert(y, thisPtr + 1, NUL, 2))  // len=2, as 3 bytes
          cacheY = INF;
      }
    }
    else if (bytes == 2)
    {
      thisPtr++;
      if (x > *thisPtr)
      {
        if (*thisPtr != 255)    // run lengths are limited to 255
          (*thisPtr)++;   // len++
      }
      else if (Insert(y, thisPtr++, NUL)) // need to go to 3 bytes
      {
        if (*thisPtr != 255)
          (*thisPtr)++;   // len++
      }
      else
        cacheY = INF;
    }
    else // 3 bytes
    {
      thisPtr += 2;
      if (*thisPtr != 255)
        (*thisPtr)++;   // len++
    }
    cacheX++;
    return;
  }

  byte* thisPtr = pool;
  byte* rowPtr = rows;
  int startRow = 0;
  // check short-cuts
  for (int midRow = numMidRows-1; midRow; midRow--)
    if (y >= midRow*SPARSE_ROWS/numMidRows)
    {
      startRow = midRow*SPARSE_ROWS/numMidRows;
      thisPtr += sumToMidRow[midRow];
      rowPtr  += startRow;
      break;
    }
  // add up the bytes per row to find the start of the data for row y
  for (int row = startRow; row < y; row++, rowPtr++)
    thisPtr += *rowPtr;

  int16_t columnOffset = 0;
  byte bytesInRow = *rowPtr;
  while (bytesInRow)
  {
    if (*thisPtr == ESC)
    {
      if (x < ESC)     // insert before ESC/thisPtr
      {
        Insert(y, thisPtr, (byte)(x - columnOffset));
        cacheX = x + 1;
        cacheY = y;
        cachePtr = thisPtr;
        cacheLast = bytesInRow == 1;
        return;
      }
      columnOffset = ESC;
      bytesInRow--;
      thisPtr++;
    }
    int16_t endX = (int16_t)(SPARSE_GET_X(thisPtr) + columnOffset + SPARSE_GET_LEN(bytesInRow == 1, thisPtr));
    if ((x - endX) >= 1)
    {
      byte bytes = SPARSE_GET_SIZE(bytesInRow == 1, thisPtr);
      bytesInRow -= bytes;
      thisPtr += bytes;
    }
    else
      break;
  }
  cacheY = INF;
  if (!bytesInRow) // append. got to the end without finding a place to insert/update
  {
    if (!columnOffset && x >= ESC)
    {
      // but we need an ESC
      Insert(y, thisPtr, ESC);
      columnOffset = ESC;
      thisPtr++;
    }
    Insert(y, thisPtr, (byte)(x - columnOffset));
    cacheX = x + 1;
    cacheY = y;
    cachePtr = thisPtr;
    cacheLast = true;
  }
  // thisPtr is an item with an x larger than ours, or within 1 of ours
  else if (x == SPARSE_GET_X(thisPtr) + columnOffset - 1)  // expand thisPtr left
  {
    if (*thisPtr)
    {
      byte bytes = SPARSE_GET_SIZE(bytesInRow == 1, thisPtr);
      (*thisPtr)--;     // x--
      if (bytes == 1)
      {
        if (x >= 2) // 2 bytes will work
          Insert(y, thisPtr + 1, 2);  // len=2
        else // need 3
          Insert(y, thisPtr + 1, NUL, 2);  // len=2, as 3 bytes
      }
      else if (bytes == 2)
      {
        thisPtr++;
        if (x > *thisPtr)
        {
          if (*thisPtr != 255)
            (*thisPtr)++;   // len++
        }
        else if (Insert(y, thisPtr++, NUL)) // need to go to 3 bytes
        {
          if (*thisPtr != 255)
            (*thisPtr)++;   // len++
        }
      }
      else // 3 bytes
      {
        thisPtr += 2;
        if (*thisPtr != 255)
          (*thisPtr)++;   // len++
      }
    }
  }
  else if (x == (SPARSE_GET_X(thisPtr) + columnOffset + SPARSE_GET_LEN(bytesInRow == 1, thisPtr))) // expand thisPtr right
  {
    byte bytes = SPARSE_GET_SIZE(bytesInRow == 1, thisPtr);
    x = SPARSE_GET_X(thisPtr);
    if (bytes == 1)
    {
      if (x >= 2) // 2 bytes will work
        Insert(y, thisPtr + 1, 2);  // len=2
      else // need 3
        Insert(y, thisPtr + 1, NUL, 2);  // len=2, as 3 bytes
    }
    else if (bytes == 2)
    {
      thisPtr++;
      if (x > *thisPtr)
      {
        if (*thisPtr != 255)
          (*thisPtr)++;   // len++
      }
      else if (Insert(y, thisPtr++, NUL)) // need to go to 3 bytes
      {
        if (*thisPtr != 255)
          (*thisPtr)++;   // len++
      }
    }
    else // 3 bytes
    {
      thisPtr += 2;
      if (*thisPtr != 255)
        (*thisPtr)++;   // len++
    }
  }
  else if (x < (SPARSE_GET_X(thisPtr) + columnOffset))     // insert before thisPtr
  {
    Insert(y, thisPtr, (byte)(x - columnOffset));
    cacheX = x + 1;
    cacheY = y;
    cachePtr = thisPtr;
    cacheLast = bytesInRow == 1;
  }

}


void Clear(int16_t originY)
{
  // prepare for another render
  rowOffset = originY;
  memset(rows, 0x00, sizeof(rows));
  memset(sumToMidRow, 0x00, sizeof(sumToMidRow));
  pool_top = 0;
  full = false;
}

void Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t minX, int16_t maxX, byte dotPattern)
{
  // Draw a line {x0, y0} to {x1, y1}. Clipped to minX..maxX. minX is redundant?
  // Always drawn left-to-right
  // Results in a series of calls to Pixel()
  // dotPattern drives dot pattern, use 0x00 for solid line (faster than 0xFF?)
  int dx, dy;
  int     sy;
  int er, e2;
  byte dotMask = 0x80;
  if (x0 > x1)
  {
    // ensure x0 <= x1;
    dx = x0; x0 = x1; x1 = dx;
    dy = y0; y0 = y1; y1 = dy;
  }
  dx = x1 - x0;
  dy = (y1 >= y0) ? y0 - y1 : y1 - y0;
  sy = (y0 <  y1) ? 1       : -1;
  er = dx + dy;

  while (true)
  {
    bool dot = true;
    if (minX <= x0 && x0 < maxX)
    {
      if (dotPattern)
      {
        if (dotMask & dotPattern)
          Pixel(x0 - minX, y0);
        else
          dot = false;
        dotMask >>= 1;
        if (!dotMask)
          dotMask = 0x80;
      }
      else
        Pixel(x0 - minX, y0);
    }
    else if (x0 > maxX)   // the rest is clipped, get out
      return;
    if ((x0 == x1) && (y0 == y1)) // done!
    {
      if (!dot) // add final dot if missing
        Pixel(x0 - minX, y0);
      return;
    }
    e2 = 2 * er;
    if (e2 >= dy)
    {
      er += dy;
      x0++;
    }
    if (e2 <= dx)
    {
      er += dx;
      y0 += sy;
    }
  }
}

void Paint(int16_t originX, int16_t originY, int16_t minRow, int16_t maxRow, int16_t maxCol, byte*& pRowStart, word fg)
{
  // Paint the sparse pixels. Left edge is inset into window by originX.
  // Rows painted are minRow..maxRow
  // pRowStart optionally points to the start in the pool, updated to the end

  LCD_BEGIN_FILL(PAINT_WINDOW_ORIGIN_X + originX, originY + PAINT_WINDOW_ORIGIN_Y + minRow, maxCol, maxRow - minRow);
  if (!pRowStart)
    pRowStart = pool;
  byte* pRow = rows + minRow;
  for (int row = minRow; row < maxRow; row++, pRow++)
  {
    byte* pValue = pRowStart;
    byte rowLen = *pRow;
    pRowStart += rowLen;
    int16_t columnOffset = 0;
    int16_t prevX = 0;
    if (rowLen)
    {
      while (rowLen)
      {
        if (*pValue == ESC)
        {
          columnOffset = ESC;
          rowLen--;
          pValue++;
        }
        int16_t x = SPARSE_GET_X(pValue) + columnOffset;
        byte len = SPARSE_GET_LEN(rowLen == 1, pValue);
        byte size = SPARSE_GET_SIZE(rowLen == 1, pValue);
        if (prevX < x)
        {
          LCD_FILL_BYTE(x - prevX, 0x00);
          LCD_FILL_COLOUR(len, fg);
          prevX = x + len;
        }
        else if (prevX < x + len)
        {
          // deal with overlaps
          int16_t extra = x + len - prevX;
          LCD_FILL_COLOUR(extra, fg);
          prevX += extra;
        }
        rowLen -= size;
        pValue += size;
      }
      if (prevX < maxCol)
      {
        LCD_FILL_BYTE(maxCol - prevX, 0x00);
      }
    }
    else
    {
      // blank row
      LCD_FILL_BYTE(maxCol, 0x00);
    }
  }
}
}
