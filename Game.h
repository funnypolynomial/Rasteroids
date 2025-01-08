#pragma once

// Game compile-time configuration
// 
// Switch between Small (240x320 Touch) and Large (320x480) LCD's
#define LCD_SMALL
#ifdef LCD_SMALL
#include "Game_Small.h"
#else
#include "Game_Large.h"
#endif

//#define DEBUG
#ifdef DEBUG
// Dump variable to serial
#define DBG(_x) { Serial.print(#_x);Serial.print(":");Serial.println(_x); }
#else
#define DBG(_x)
#endif

#define SPARSE SparseXL

// Configuration, disabling these can increase the frame-rate
#define ENABLE_SCORE                // Show Score
#define ENABLE_LIVES                // Show Lives 
#define ENABLE_ATARI       1        // Show (c) Atari if defined.  0 for slow DVG version, 1 for faster/direct version
#define ENABLE_TIME_SCORE           // Show Time as the Score {#}
#define ENABLE_TIME_24HOUR          // Show Time is 24-hour (vs 12-hour) {#}
// {#}: N/A if there is no RTC connected

#define OPTION_SCORE  9999          // Score if not shown as Time (0..9999)
#define OPTION_LIVES     3          // Lives (ships) if shown

//#define DEBUG_STACK_CHECK          // Check that there's enough stack. Headroom (unused stack) reported in score

namespace Game
{
  // The main game logic
  void Splash();
  void Init();
  void Randomize(unsigned long ms);
  void CheckInteraction();
  void Draw();
  void AnimationStep();

  void GetElementPixelPositions(int16_t& TimeY, int16_t& LivesY);
  void PaintConfigTime(uint8_t hour24, uint8_t min, uint8_t mask);
  extern uint16_t animationStep;
};
