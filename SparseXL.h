#pragma once

// Sparse pixel representation, the key to making this work on an Arduino
// Large version
namespace SparseXL
{
  extern uint16_t highWater;
  extern bool full;
  void Clear(int16_t originY);
  void Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t minX, int16_t maxX, byte dotPattern = 0x00);
  void Paint(int16_t originX, int16_t originY, int16_t minRow, int16_t maxRow, int16_t maxCol, byte*& pRowStart, word fg);
};
