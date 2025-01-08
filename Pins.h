#pragma once
#include <Arduino.h>
#include "Game.h"

// Both variants use LCD shields so the only pins of interest are: 
//   SDA/SCL for an RTC, if present
//   SET/ADJ for push-buttons, if present 
// Both shields use D2-D9 for data and A0-A4 for control
// The small LCD uses A2+D8 for touch-x & A3+D9 for touch-y

#ifdef LCD_SMALL
// *** Small ***
#define PIN_RTC_SDA   12
#define PIN_RTC_SCL   11

// no buttons (touch screen) 
#else
// *** Large ***
#define PIN_BTN_SET   A7 // if analog, negate for BTN::Init
#define PIN_BTN_ADJ   A6

#define PIN_RTC_SDA   12
#define PIN_RTC_SCL   11

#endif
