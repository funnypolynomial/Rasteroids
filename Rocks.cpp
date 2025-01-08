#include <Arduino.h>
#include "Game.h"
#include "DVG.h"
#include "VGROM.h"
#include "SparseXL.h"
#include "Objects.h"
#include "Rocks.h"

namespace Rocks {
  constexpr int8_t  MaxRocks = 10;
  // fixed number of rock "slots" some may be empty/none
  Objects::Object rocks[MaxRocks];

  constexpr uint16_t RockScalesPacked = (DVG::UnityScale | (DVG::Div2Scale << 4) | (DVG::Div4Scale << 8));
  constexpr uint16_t RockSizesPacked  = 0x1D96; // large=132, medium=72, small=42, packed divided by 6, 5 bits each

  void SetSize(Objects::Object* pRock, uint8_t scale)
  {
    // Set the rock's size & scale info, scale = 0, 1, 2 corresponds to // /1, /2 or /4
    pRock->scaleFactor = (scale << 4) | ((RockScalesPacked >> 4*scale) & 0x0F);
    pRock->size = 6*((RockSizesPacked >> (5*scale)) & 0b00011111);
  }

  void SetSpeed(Objects::Object* pRock)
  {
    // Set the rock's speed, X & Y speeds are -31...-6 or +6...+31
    uint8_t bits = Objects::Random(4);
    pRock->dX = Objects::Random(6, 32) << Objects::SpeedShiftFactor;
    pRock->dY = Objects::Random(6, 32) << Objects::SpeedShiftFactor;
    if (bits & 0x01)
      pRock->dX = -pRock->dX;
    if (bits & 0x02)
      pRock->dY = -pRock->dY;
  }

  void BreakRock(Objects::Object* pRock, uint8_t scale)
  {
    // Splits the rock in two, see BreakAsteroid:
    SetSize(pRock, scale);
    SetSpeed(pRock);
    Objects::Object* pRock2 = Objects::GetFreeSlot(rocks, MaxRocks);
    if (pRock2)
    {
      pRock2->type = Objects::Random(4);
      SetSize(pRock2, scale);
      SetSpeed(pRock2);
      pRock2->X = pRock->X;
      pRock2->Y = pRock->Y;
      // offset position by the low 5 bits of the velocity (*2 originally, but we double the speed)
      pRock2->X ^= (pRock2->dX & 0x1F) << (1 - Objects::SpeedShiftFactor);
      pRock2->Y ^= (pRock2->dY & 0x1F) << (1 - Objects::SpeedShiftFactor);;
    }
  }

  void Random(Objects::Object* pRock)
  {
    // Make a random rock in the given slot
    // type/size
    pRock->type = Objects::Random(Objects::Rock3 + 1);
    SetSize(pRock, Objects::Random(0x03));
    SetSpeed(pRock);
    if (Objects::Random(2))
      pRock->Y = Objects::Random(Objects::maxY); // originates at left/right of screen
    else
      pRock->X = Objects::Random(Objects::maxX);  // starts at top/bottom of screen.
  }

  void Random(uint8_t idx)
  {
    // as above but via index
    Random(rocks + idx);
  }

  void Splash(int y, int dy)
  {
    // make rocks for the splash, all the rocks, large, fast, in from the left, arranged by y, dy
    ::memset(rocks, Objects::None, sizeof(rocks));
    for (int r = Objects::Rock0; r <= Objects::Rock3; r++)
    {
      rocks[r].type = (Objects::Type)r;
#ifdef LCD_SMALL
      rocks[r].scaleFactor = DVG::UnityScale;
      rocks[r].size  = 132;
#else      
      rocks[r].scaleFactor = DVG::Div2Scale;
      rocks[r].size  = 72;
#endif
      rocks[r].X = 0;
      rocks[r].Y = y + dy*r;
      rocks[r].dX = +32 << Objects::SplashSpeedShiftFactor;
      rocks[r].dY = 0;
      rocks[r].wrap = false;
    }
  }

  void InitWave()
  {
    // create some rocks
    ::memset(rocks, Objects::None, sizeof(rocks));
    for (uint8_t i = 0; i < MaxRocks/2; i++)
      Random(i);
  }

  void Draw()
  {
    // just paint the rocks
    Objects::Object* pRock = rocks;
    for (int idx = 0; idx < MaxRocks; idx++, pRock++)
      Objects::Draw(*pRock);
  }

  void AnimationStep()
  {
    // move rocks, consider adding a new one
    int count = 0;
    Objects::Object* pRock = rocks;
    for (int idx = 0; idx < MaxRocks; idx++, pRock++)
      if (Objects::AnimationStep(*pRock))
        count++;

    // periodically check the number of rocks
    if (Game::animationStep % 256 == 0 || count < 2)
    {
      // probability of a new rock goes down with the current count
      if (count < MaxRocks && (pRock = Objects::GetFreeSlot(rocks, MaxRocks)) && Objects::Random(100) >= count*count)
        Random(pRock);
    }
  }

  bool HitTest(Objects::Object& obj, int16_t& X, int16_t& Y)
  {
    // returns true if obj hits one of the rocks, sets X & Y to position of rock
    // called before animation step
    // doesn't account for (bullet) speed? 
    Objects::Object* pRock = rocks;
    if (obj.type != Objects::None)
      for (int idx = 0; idx < MaxRocks; idx++, pRock++)
        if (pRock->type != Objects::None)
        {
          // approximate hit, good enough and compact as 6502, see label "HitDectection:"
          int dx = abs(obj.X - pRock->X);
          int dy = abs(obj.Y - pRock->Y);
          int box = obj.size + pRock->size; // hit box x1.5, "about sqrt(2)...more circular"
          // sqrt(boxX^2 + boxY^2) = sqrt(2*boxSize^2) = sqrt(2)*boxSize ~= 1.5*boxSize
          box += box >> 1;
          if ((dx + dy) <= box)   // HIT!
          {
            X = pRock->X;
            Y = pRock->Y;
            uint8_t scale = pRock->scaleFactor >> 4;
            if (scale != 2)
              BreakRock(pRock, scale + 1);    // halve & split
            else
              pRock->type = Objects::None;     // destroyed
            return true;
          }
        }
    return false;
  }
}
