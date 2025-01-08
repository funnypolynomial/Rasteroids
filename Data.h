#pragma once

namespace Data
{
  // Various PROGMEM data

  const uint32_t* Atari(int& width, int& height);

  constexpr int   ButtonSize = 32;
  const word*     ButtonPalette(bool set);
  const uint8_t*  ButtonImage(bool down);

  const uint8_t*  Font();
};
