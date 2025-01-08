#include <Arduino.h>
// Libraries:
#include <SoftwareI2C.h>

#include "SparseXL.h"
#include "Game.h"
#include "Pins.h"
#include "DVG.h"
#include "VGROM.h"
#include "RTC.h"
#include "Objects.h"
#include "Rocks.h"
#include "BTN.h"

//                                         Rasteroids
// DOES NOT PROVIDE GAMEPLAY!
// A toy-like approximation of 1979's Asteroids game's "Attract" (demo) mode.  Can show the time, so a desk accessory perhaps.
//
// This follows on from two similar projects: 
//    ElitePetite ("Elite", https://github.com/funnypolynomial/ElitePetite, https://hackaday.io/project/183107-elitepetite) and 
//    LittleZone ("Battlezone", https://github.com/funnypolynomial/LittleZone, https://hackaday.io/project/185693-littlezone)
//
// The graphics are close to the original -- I emulate the Digital Vector Generator and use the original Vector Generator ROM data.
// This would not have been possible without resources like http://computerarcheology.com/Arcade/Asteroids/ & https://6502disassembly.com/va-asteroids/
// Also, YouTube videos like  https://www.youtube.com/watch?v=QsMw6uqEQDA were very useful.
//
// What it does:
//  The score and lives are displayed at top left.
//  Rocks (asteroids) drift around, 3 different kinds, 3 different sizes.  There are no "waves" as such.
//  Periodically, a large or small saucer will pass through, occasionally changing direction, and occasionally firing random bullets.
//  There is collision detection between the saucer and asteroids.
//
// Clock
//  If an RTC is present the simulation can show the time as the score in 12 or 24 hour mode
//
// What's not implemented:
//  The ship
//  Asteroid waves etc
//  "1 COIN 1 PLAY" etc
//  
// What's different:
//  A lot.  I've just tried to get the "vibe".
//
// Customization:
//  Refer to the ENABLE_ and OPTION_ defines in Game.h to configure time display, lives etc.
//  Refer to RTC_I2C_ADDRESS in RTC.h if no RTC is present
//
// Configuration:
//  Touch: 
//    With a touch screen, tapping up near the score/lives configures the time (or is ignored).
//      The time is shown as HHMM. Two buttons are drawn: "SET" & "ADJ". 
//      Tapping SET accepts the current (blinking) field (or the time)
//      Tapping ADJ increments the current field.
//      Tapping below the score/lives exits without setting the time.
//   Tapping below score/lives resets the game.
//  Buttons: 
//    With push-buttons, pressing SET sets the time (as above). ADJ increments the current value, SET advances to the next field.
//    Pressing SEL resets game as above.
//
// LCD:
//  The Game's interface to an LCD is defined by the 7 LCD_ macros in Game_<size>.h
//  Note also the XC4630_HX8347i define for different revisions of the small LCD
//  There are also defines for left/right landscape orientation
//  XC4630_TOUCH_CALIB/CHECK for touch-screen calibration/check
//
// How:
//   Something like an Uno just doesn't have the RAM to create frames in the traditional sense.
//   My solution is SparseXL which does on-the-fly RLE encoding of the game logic's pixel writes.
//   Essentially a compressed frame. That data is then sent to the LCD in one update.
//
// Notes:
// "Low memory available, stability problems may occur."
//   This compiles for an Uno with the dire warning above. But see DEBUG_STACK_CHECK. 
//   This reports the headroom after local variables and return addresses are pushed on the stack.
//   Relatively simple to do since the main loop is basically the same.  
//   It shows of the ~340 bytes available (after globals including SparseXL::pool consume half of the 2048 bytes),
//   only ~130 are needed on the stack (DEBUG, LCD_SMALL).
//
// Verified to run on an Uno and a Mega.
//
// Mark Wilson, Jan 2025

#ifdef DEBUG_STACK_CHECK
// see, for example, https://www.avrfreaks.net/s/topic/a5C3l000000U8hmEAC/t047260
extern uint8_t _end;
uint8_t stackFill = 0;
uint16_t stackHeadroom = 9999;
void StackPaint()
{
  // Fill bytes from the top of dynamic variables up to the top of our stack
  uint8_t* ptr = &_end;
  stackFill++;  // different value each time
  while (ptr < (uint8_t*)&ptr)
  {
    *ptr = stackFill;
    ptr++;
  }
} 

void StackCheck()
{
  // Check bytes from the top of dynamic variables up to the bottom of our stack
  // Updates stackHeadroom
  const uint8_t *ptr = &_end;
  uint16_t       ctr = 0;
  while (*ptr == stackFill && ptr < (uint8_t*)&ptr)
  {
    ptr++;
    ctr++;
  }
  if (ctr < stackHeadroom)
    stackHeadroom = ctr;
}
#else
#define StackPaint()
#define StackCheck()
#endif

void setup() 
{ 
#ifdef DEBUG  
  Serial.begin(38400);
  Serial.println("Rasteroids");
#endif  
#if defined(PIN_BTN_SET) && defined(PIN_BTN_ADJ)
  btn1Set.Init(-PIN_BTN_SET); // these are analog
  btn2Adj.Init(-PIN_BTN_ADJ);  
#endif
  rtc.Setup();
  LCD_INIT();
  LCD_FILL_BYTE(LCD_BEGIN_FILL(0, 0, LCD_WIDTH, LCD_HEIGHT), 0x00);
#ifndef DEBUG
  Game::Splash();
  Game::Randomize(0);
#endif  
  Game::Init();
}

void loop() 
{
  StackPaint();
  Game::AnimationStep();
  Game::Draw();
  Game::CheckInteraction();
  StackCheck();
}
