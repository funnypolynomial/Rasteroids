#pragma once
// Small version uses 240x320 LCD Touch Screen Shield, https://www.jaycar.co.nz/240x320-lcd-touch-screen-for-arduino/p/XC4630, SPFD5408 interface?
// --OR-- later revision of above, HX8347i, see XC4630_HX8347i define
#include "LCD.h"
// The LCD interface
// Initialise
#define LCD_INIT() lcd.init();
// Define a window to fill with pixels at (_x,_y) width _w, height _h
// Returns the number of pixels to fill (unsigned long)
#define LCD_BEGIN_FILL(_x,_y,_w,_h) lcd.beginFill(_x,_y,_w,_h)
// Sends _sizeUL (unsigned long) pixels of the 16-bit colour
#define LCD_FILL_COLOUR(_sizeUL, _colorWord) lcd.fillColour(_sizeUL, _colorWord)
// Sends _sizeUL (unsigned long) pixels of the 8-bit colour.
// The byte is duplicated, 0xFF and 0x00 really only make sense. Slightly faster than above.
#define LCD_FILL_BYTE(_sizeUL, _colorByte) lcd.fillByte(_sizeUL, _colorByte)
// Sends a single white pixel
#define LCD_ONE_WHITE() lcd.fillByte(1, 0xFF)
// Sends a single black pixel
#define LCD_ONE_BLACK() lcd.fillByte(1, 0x00)
// True if there is a touch. Returns position in (int) _x, _y
#define LCD_GET_TOUCH(_x, _y) lcd.getTouch(_x, _y)


// The whole LCD
#define LCD_WIDTH  XC4630_WIDTH
#define LCD_HEIGHT XC4630_HEIGHT

// The Game screen
#define SCREEN_WIDTH  LCD_WIDTH
#define SCREEN_HEIGHT LCD_HEIGHT
// 320/1024 (and 240/768) == 5/16
#define SCREEN_SCALE_NUM 5
#define SCREEN_SCALE_DEN 16

#define SCREEN_OFFSET_X ((LCD_WIDTH - SCREEN_WIDTH)/2)
#define SCREEN_OFFSET_Y ((LCD_HEIGHT - SCREEN_HEIGHT)/2)

#define GAME_BEAM_WIDTH 768
