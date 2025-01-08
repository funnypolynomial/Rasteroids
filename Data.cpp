#include <Arduino.h>
#include "Game.h"
#include "Data.h"

namespace Data
{
  static const uint32_t pAtari[] PROGMEM =
  {
    // "(c) Atari..." pixels. Hand-crafted approximations to scaled rendered text, made legible even at small-szie
  #ifdef LCD_SMALL
  #define ATARI_WIDTH 64
  #define ATARI_HEIGHT 5
    0b01000010000010111011101110000010, 0b01110010011101110000111011101110,
    0b10011001000010101000101010000101, 0b00100101010100100000010010101000,
    0b10010001000010111000101110000111, 0b00100111011100100000010010101000,
    0b10011001000010001000100010000101, 0b00100101011000100000010010101000,
    0b01000010000010001000100010000101, 0b00100101010101110000111010101110,
  #else
  #define ATARI_WIDTH 84
  #define ATARI_HEIGHT 6
    0b01000010000101111101111101111100, 0b00001000111110001000111110111110, 0b00011111010001011111000000000000,
    0b10011001000101000100000101000100, 0b00010100001000010100100010001000, 0b00000100011001010000000000000000,
    0b10100001000101111100000101111100, 0b00100010001000100010111110001000, 0b00000100010101010000000000000000,
    0b10100001000100000100000100000100, 0b00111110001000111110101000001000, 0b00000100010101010000000000000000,
    0b10011001000100000100000100000100, 0b00100010001000100010100100001000, 0b00000100010011010000000000000000,
    0b01000010000100000100000100000100, 0b00100010001000100010100010111110, 0b00011111010001011111000000000000,
    //                                                                                 ends here ^
  #endif
    0,
  };

  const uint32_t* Atari(int& width, int& height)
  {
    width = ATARI_WIDTH;
    height = ATARI_HEIGHT;
    return pAtari;
  }

  // colours & pixel data for the two touch buttons
  static const word SetPalette[] PROGMEM =
  {
    RGB(0,0,0),
    RGB(255,0,0),
    RGB(255,255,255)
  };

  static const word AdjPalette[] PROGMEM =
  {
    RGB(0,0,0),
    RGB(0,0,255),
    RGB(255,255,255)
  };

    // Config push-button image data
  // each byte is 0bnnnnnnpp where nnnnnn is the length and pp is the palette index
  static const uint8_t ButtonUpImage[] PROGMEM =
  {
    0x28, 0x2E, 0x2C,
    0x20, 0x0A, 0x2D, 0x0A, 0x24,
    0x18, 0x0A, 0x3D, 0x0A, 0x1C,
    0x14, 0x55, 0x18,
    0x10, 0x5D, 0x14,
    0x0C, 0x21, 0x26, 0x21, 0x10,
    0x08, 0x1D, 0x0A, 0x25, 0x0A, 0x1D, 0x0C,
    0x08, 0x19, 0x04, 0x35, 0x04, 0x19, 0x0C,
    0x04, 0x19, 0x04, 0x3D, 0x04, 0x19, 0x08,
    0x04, 0x19, 0x04, 0x3D, 0x04, 0x19, 0x08,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x04, 0x19, 0x04, 0x3D, 0x04, 0x19, 0x08,
    0x04, 0x19, 0x04, 0x3D, 0x04, 0x19, 0x08,
    0x08, 0x19, 0x04, 0x35, 0x04, 0x19, 0x0C,
    0x08, 0x19, 0x0C, 0x25, 0x0C, 0x19, 0x0C,
    0x0C, 0x15, 0x3C, 0x15, 0x10,
    0x10, 0x15, 0x34, 0x15, 0x14,
    0x14, 0x19, 0x24, 0x19, 0x18,
    0x18, 0x4D, 0x1C,
    0x20, 0x3D, 0x24,
    0x28, 0x2D, 0x2C,
    0x80,
    0x00
  };

  static const uint8_t ButtonDownImage[] PROGMEM =
  {
    0x28, 0x2E, 0x2C,
    0x20, 0x0A, 0x2D, 0x0A, 0x24,
    0x18, 0x0A, 0x3D, 0x0A, 0x1C,
    0x14, 0x55, 0x18,
    0x10, 0x5D, 0x14,
    0x0C, 0x21, 0x24, 0x21, 0x10,
    0x08, 0x1D, 0x34, 0x1D, 0x0C,
    0x08, 0x19, 0x0C, 0x25, 0x0C, 0x19, 0x0C,
    0x04, 0x19, 0x08, 0x35, 0x08, 0x19, 0x08,
    0x04, 0x19, 0x08, 0x35, 0x08, 0x19, 0x08,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x15, 0x04, 0x4D, 0x04, 0x15, 0x04,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x19, 0x04, 0x45, 0x04, 0x19, 0x04,
    0x04, 0x19, 0x04, 0x3D, 0x04, 0x19, 0x08,
    0x04, 0x19, 0x04, 0x3D, 0x04, 0x19, 0x08,
    0x08, 0x19, 0x06, 0x35, 0x06, 0x19, 0x0C,
    0x08, 0x1D, 0x0A, 0x25, 0x0A, 0x1D, 0x0C,
    0x0C, 0x21, 0x26, 0x21, 0x10,
    0x10, 0x5D, 0x14,
    0x14, 0x55, 0x18,
    0x18, 0x4D, 0x1C,
    0x20, 0x3D, 0x24,
    0x28, 0x2D, 0x2C,
    0x80,
    0x00
  };

  const word* ButtonPalette(bool set)
  {
    return set?SetPalette:AdjPalette;
  }

  const uint8_t* ButtonImage(bool down)
  {
    return down?ButtonDownImage:ButtonUpImage;
  }

  //--------------------------------------------------------
// (Part of) The BBC font
#define X (1)
#define _ (0)

#define LINE(_a, _b, _c, _d, _e, _f, _g, _h) ((_a << 7) | \
                                              (_b << 6) | \
                                              (_c << 5) | \
                                              (_d << 4) | \
                                              (_e << 3) | \
                                              (_f << 2) | \
                                              (_g << 1) | \
                                              (_h << 0))

  static const byte pFont[] PROGMEM =
  {
    LINE(_,_,X,X,X,X,_,_), // S
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,_,_,_,_),
    LINE(_,_,X,X,X,X,_,_),
    LINE(_,_,_,_,_,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,_,X,X,X,X,_,_),
    LINE(_,_,_,_,_,_,_,_),

    LINE(_,X,X,X,X,X,X,_), // E
    LINE(_,X,X,_,_,_,_,_),
    LINE(_,X,X,_,_,_,_,_),
    LINE(_,X,X,X,X,X,_,_),
    LINE(_,X,X,_,_,_,_,_),
    LINE(_,X,X,_,_,_,_,_),
    LINE(_,X,X,X,X,X,X,_),
    LINE(_,_,_,_,_,_,_,_),

    LINE(_,X,X,X,X,X,X,_), // T
    LINE(_,_,_,X,X,_,_,_),
    LINE(_,_,_,X,X,_,_,_),
    LINE(_,_,_,X,X,_,_,_),
    LINE(_,_,_,X,X,_,_,_),
    LINE(_,_,_,X,X,_,_,_),
    LINE(_,_,_,X,X,_,_,_),
    LINE(_,_,_,_,_,_,_,_),

    LINE(_,_,X,X,X,X,_,_), // A
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,X,X,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,_,_,_,_,_,_,_),

    LINE(_,X,X,X,X,_,_,_), // D
    LINE(_,X,X,_,X,X,_,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,_,X,X,_),
    LINE(_,X,X,_,X,X,_,_),
    LINE(_,X,X,X,X,_,_,_),
    LINE(_,_,_,_,_,_,_,_),

    LINE(_,_,X,X,X,X,X,_), // J
    LINE(_,_,_,_,X,X,_,_),
    LINE(_,_,_,_,X,X,_,_),
    LINE(_,_,_,_,X,X,_,_),
    LINE(_,_,_,_,X,X,_,_),
    LINE(_,X,X,_,X,X,_,_),
    LINE(_,_,X,X,X,_,_,_),
    LINE(_,_,_,_,_,_,_,_),
  };

  const uint8_t* Font()
  {
    return pFont;
  }

}
