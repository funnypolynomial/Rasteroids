#include <Arduino.h>
#include "Game.h"
#include "DVG.h"
#include "SparseXL.h"


#include "VGROM.h"

namespace DVG 
{
// cursor coords in CRT space
int16_t cur_beam_X = 0;   // x=0...1023
int16_t cur_beam_Y = 0;   // y=0...1023, or actually 768?
const uint16_t* ReturnAddr = NULL;
int8_t globalScaleSignedShift = 1;

int16_t Scale(int32_t s, int32_t num, int32_t den)
{
  // scale by num/den with rounding
  int32_t round = 0;
  if (s >= 0)
    round = ((+s*num) % den) > (den/2) ? +1 : 0;
  else
    round = ((-s*num) % den) > (den/2) ? -1 : 0;
  return num*s/den + round;
}

int16_t ScaleX(int16_t x)
{
  // scale & transform CRT coord to pixels
  return Scale(x, SCREEN_SCALE_NUM, SCREEN_SCALE_DEN);
}

int16_t ScaleY(int16_t y)
{
  // scale & transform CRT coord to pixels
  return SCREEN_HEIGHT - Scale(y, SCREEN_SCALE_NUM, SCREEN_SCALE_DEN);
}

// Combine local & global scale factors
#define CombinedScale(_len, _local) (_len) >> (_local + globalScaleSignedShift)

void Draw(int16_t dX, int16_t dY, int16_t I, int16_t vectorScalePercent)
{
  // Draw a line from current postion to {dX, dY} with the given intensity and scale
  if (vectorScalePercent != 100)
  {
    dX = Scale(dX, vectorScalePercent, 100);
    dY = Scale(dY, vectorScalePercent, 100);
  }
  if (I)
  {
    int16_t x0 = ScaleX(cur_beam_X), y0 = ScaleY(cur_beam_Y);
    cur_beam_X += dX;
    cur_beam_Y += dY;
    SPARSE::Line(x0, y0, ScaleX(cur_beam_X), ScaleY(cur_beam_Y), 0, SCREEN_WIDTH);
  }
  else
  {
    cur_beam_X += dX;
    cur_beam_Y += dY;
  }
}

void MoveBeamTo(int16_t X, int16_t Y)
{
  cur_beam_X = X;
  cur_beam_Y = Y;
}

void MoveBeam(int16_t dX, int16_t dY)
{
  Draw(dX, dY, 0x00, 100);
}

void DrawBeam(int16_t dX, int16_t dY)
{
  Draw(dX, dY, 0x0F, 100);
}

void Cursor(int16_t X, int16_t Y, int8_t globalScale)
{
  // set the beam position and the scale
  MoveBeamTo(X, Y);
  // 0b1111=/2 ... 0b1001=/128
  // 0b0000=*1 or /512?
  // 0b0001=*2 ... 0b0111=*128 (vecgen.pdf)    
  if (globalScale & 0x08)
    globalScaleSignedShift = (8 - (globalScale & 0x07));
  else
    globalScaleSignedShift = -globalScale;
}

void Text(const char* str, int16_t scalePercent, bool progmem)
{
  // draw the text at the cursor position, str is normal memory or PROGMEM
  while (progmem?pgm_read_byte_near(str):*str)
  {
    uint8_t idx = 0;
    char ch = progmem?pgm_read_byte_near(str):*str;
    if ('0' <= ch && ch <= '9')
      idx = ch - '0' + 1;
    else if ('A' <= ch && ch <= 'Z')
      idx = ch - 'A' + 11;
    Run(VGROM::Char(idx), scalePercent);
    str++;
  }
}

void Run(uint16_t offset, int16_t scalePercent)
{
  // Execute the ROM beam commands from the offset, with the scale
  const uint16_t* pCmd = VGROM::Base() + offset;
  ReturnAddr = NULL;
  bool firstOp = true;
  bool run = true;
  while (run)
  {
    uint16_t cmd = pgm_read_word_near(pCmd);
    uint8_t opcode = cmd >> 12;
    switch (opcode)
    {
    case 0x0A:  // Position and global scale     1010 00YY YYYY YYYY | SSSS 00XX XXXX XXXX
    {
      // ignored, things are placed by game logic
      //int16_t Y = cmd & 0x03FF;
      //cmd = pgm_read_word_near(++pCmd);
      //int16_t X = cmd & 0x03FF;
      //Cursor(X, Y, cmd >> 12);
      break;
    }
    case 0x0B:  // Halt                         1011 0000 0000 0000
    {
      run = false;
      break;
    }
    case 0x0C:  // Jump to subroutine           1100 AAAA AAAA AAAA
    {
      // Treat starting with a JSR as a special case, return when it does
      if (!firstOp)
        ReturnAddr = pCmd;
      pCmd = VGROM::Base() + VGROM::AddrToOffset(cmd & 0x0FFF) - 1;
      break;
    }
    case 0x0D:  // Return from subroutine       1101 0000 0000 0000
    {
      if (ReturnAddr)
      {
        pCmd = ReturnAddr;
        ReturnAddr = NULL;
      }
      else
        run = false;
      break;
    }
    case 0x0E:  // Jump                         1110 AAAA AAAA AAAA
    {
      pCmd = VGROM::Base() + VGROM::AddrToOffset(cmd & 0x0FFF) - 1;
      break;
    }
    case 0x0F:  // Draw short relative vector   1111 smYY IIII SmXX
    {
      // scale factor is adjusted 0b00 => 0b10 
      int8_t localScale = 9 - ((((cmd >> 11) & 0x01) | ((cmd >> 2) & 0x02)) + 2);
      // YY & XX are upper bits of 10-bit (unsigned) coords
      int16_t Y = CombinedScale((((cmd >> 8) & 0x03) << 8), localScale);
      if (cmd & 0x0400)
        Y = -Y;
      int16_t I = (cmd >> 4) & 0x0F;
      int16_t X = CombinedScale(((cmd & 0x03) << 8), localScale);
      if (cmd & 0x004)
        X = -X;
      Draw(X, Y, I, scalePercent);
      break;
    }
    default:  // Draw relative vector.          SSSS -mYY YYYY YYYY | IIII -mXX XXXX XXXX
    {
      int8_t localScale = 9 - opcode;
      int16_t Y = CombinedScale((cmd & 0x03FF), localScale);
      if (cmd & 0x0400)
        Y = -Y;
      cmd = pgm_read_word_near(++pCmd);
      int16_t I = cmd >> 12;
      int16_t X = CombinedScale((cmd & 0x03FF), localScale);
      if (cmd & 0x0400)
        X = -X;
      Draw(X, Y, I, scalePercent);
      break;
    }
    }
    pCmd++;
    firstOp = false;
  }
}

void DrawDot()
{
  // just a dot
  SPARSE::Line(ScaleX(cur_beam_X), ScaleY(cur_beam_Y), ScaleX(cur_beam_X), ScaleY(cur_beam_Y), 0, SCREEN_WIDTH);
}

}
