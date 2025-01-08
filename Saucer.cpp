#include <Arduino.h>
#include "Game.h"
#include "DVG.h"
#include "VGROM.h"
#include "SparseXL.h"
#include "Objects.h"
#include "Rocks.h"
#include "Bullets.h"
#include "Saucer.h"


namespace Saucer {
  // these are frame counters
  #define TIMER_NEW 250 // new saucer
  #define TIMER_FIRE_START 100 // saucer starts firing
  #define TIMER_FIRE_NEXT  5   // saucer fires again
  #define FIRE_MAX  4          // saucer fires 4 times
  uint8_t timerNew = TIMER_NEW;
  uint8_t timerFire = TIMER_FIRE_START;
  uint8_t fireCounter = 0;

  uint8_t explosionStep = 0xFF;
  uint16_t explosionScales = 0;
  int16_t X2 = 0;
  int16_t Y2 = 0;
  Objects::Object saucer;

  void Init()
  {
    // init the saucer
    saucer.type = Objects::Saucer;
    bool large = Objects::Random(2);
    bool leftToRight = Objects::Random(2);
    saucer.scaleFactor = ((large ? 0 : 1) << 4) | (large ? DVG::UnityScale : DVG::Div2Scale);
    saucer.size  = large ? 78 : 60;
    saucer.X = leftToRight ? 0 : Objects::maxX;
    saucer.Y = Objects::Random(Objects::maxY);
    saucer.dX = +32 << Objects::SpeedShiftFactor;
    if (!leftToRight)
      saucer.dX = -saucer.dX;
    saucer.dY = 0;
    saucer.wrap = true;
    explosionStep = 0xFF;
    timerNew = TIMER_NEW;
    timerFire = TIMER_FIRE_START;
    fireCounter = 0;
  }

  void Splash(int y)
  {
    // make a saucer for the splash -- large, in from the left, faster
    saucer.type = Objects::Saucer;
#ifdef LCD_SMALL
    saucer.scaleFactor = DVG::UnityScale;
    saucer.size  = 78;
#else      
    saucer.scaleFactor = DVG::Div2Scale;
    saucer.size  = 60;
#endif
    saucer.X = 0;
    saucer.Y = y;
    saucer.dX = +32 << Objects::SplashSpeedShiftFactor;
    saucer.dY = 0;
    saucer.wrap = false;
  }
  
  bool Exists()
  {
    // true if saucer present
    return saucer.type != Objects::None;
  }

  void Draw()
  {
    // draw the saucer or an evolving explosion
    if (explosionStep != 0xFF)
    {
      // two shrapnel clouds
      DVG::Cursor(saucer.X, saucer.Y, explosionScales & 0x0F);
      DVG::Run(VGROM::Shrapnel(explosionStep));
      DVG::Cursor(X2, Y2, explosionScales & 0x0F);
      DVG::Run(VGROM::Shrapnel(explosionStep));
    }
    else
      Objects::Draw(saucer);
  }

  void AnimationStep()
  {
    // advance the saucer's state
    if (explosionStep != 0xFF)
    {
      // advance explosion. the 4 different patterns (each a bit bigger) for 4 different scales (each 2x bigger)
      explosionStep++;
      if ((explosionStep % 4) == 0)
        explosionScales >>= 4;  // every 4th image double the scale
      if (explosionStep >= 15)
        explosionStep = 0xFF;   // end expansion
    }
    else
    {
      if (saucer.type == Objects::None)
      {
        // saucer has gone, count down to a new one
        if (timerNew)
          timerNew--;
        else
          Init();
      }
      else if (Rocks::HitTest(saucer, X2, Y2))
      {
        // start explosion...
        // set scale sequence to /4, /2, /1, *2
        explosionScales = (DVG::Mul2Scale << 12) | (DVG::UnityScale << 8) | (DVG::Div2Scale << 4) | (DVG::Div4Scale);
        explosionStep = 0;
        saucer.type = Objects::None; // stop drawing saucer
        // pre-scale positions of the two shrapnel clouds, one where the saucer was, one where the rock was
        X2 >>= Objects::PositionShiftFactor;
        Y2 >>= Objects::PositionShiftFactor;
        saucer.X >>= Objects::PositionShiftFactor;
        saucer.Y >>= Objects::PositionShiftFactor;
        timerNew = TIMER_NEW/2; // killed, start counter (shorter)
      }
      else
      {
        // new saucer
        timerNew--;
        if (timerNew == 0)
        {
          saucer.wrap = false; // let it go off-screen
          timerNew = TIMER_NEW; // and start counter
        }

        // random fire
        timerFire--;
        if (timerFire == 0)
        {
          fireCounter++;
          if (fireCounter <= FIRE_MAX && Bullets::Fire(&saucer))
            timerFire = TIMER_FIRE_NEXT; // fire again
          else
          {
            timerFire = TIMER_FIRE_START; // restart
            fireCounter = 0;
          }
        }

        else if (Game::animationStep % 64 == 0) // Randomly change saucer Y velocity every n frames.
        {
          uint8_t dY = (uint8_t)(0x90000010UL >> (8*Objects::Random(4))); // -16,0,0,+16
          saucer.dY = (dY & 0x7F) << Objects::SpeedShiftFactor;
          if (dY & 0x80)
            saucer.dY = -saucer.dY;
        }
        Objects::AnimationStep(saucer);
      }
    }
  }
}
