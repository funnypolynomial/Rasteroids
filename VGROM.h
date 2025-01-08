#pragma once

namespace VGROM
{
  // Vector Generator ROM.
  const uint16_t BaseAddress = 0x0800;
  const uint16_t* Base();
  uint16_t AddrToOffset(uint16_t addr);

  uint16_t Credits();
  uint16_t Saucer();
  uint16_t Rock(uint8_t index);
  uint16_t Lives();
  uint16_t Shrapnel(uint8_t index);
  uint16_t Char(uint8_t index);
};
