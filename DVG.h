#pragma once

namespace DVG
{
  // Digital Vector Generator
  enum GlobalScale
  {
    UnityScale = 0x00,

    Mul2Scale  = 0x01,
    Mul4Scale  = 0x02,
    Mul8Scale  = 0x03,

    Div8Scale  = 0x0D,
    Div4Scale  = 0x0E,
    Div2Scale  = 0x0F,
  };

  constexpr int16_t beamWidth  = 1024;
  constexpr int16_t beamHeight = GAME_BEAM_WIDTH;

  void Run(uint16_t offset, int16_t scalePercent = 100);
  void Cursor(int16_t X, int16_t Y, int8_t globalScale);
  void Text(const char* str, int16_t scalePercent = 100, bool progmem = false);

  void MoveBeamTo(int16_t X, int16_t Y);
  void MoveBeam(int16_t dX, int16_t dY);
  void DrawBeam(int16_t dX, int16_t dY);
  void Draw(int16_t dX, int16_t dY, int16_t I, int16_t vectorScalePercent);
  void DrawDot();

  int16_t Scale(int32_t s, int32_t num, int32_t den);
  // scale & transform CRT coord to pixels
  int16_t ScaleX(int16_t x);
  int16_t ScaleY(int16_t y);
};
