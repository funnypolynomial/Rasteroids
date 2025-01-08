#include <Arduino.h>
#include "Game.h"
#include "DVG.h"
#include "VGROM.h"
#include "SparseXL.h"
#include "Objects.h"
#include "Rocks.h"
#include "Bullets.h"

namespace Bullets {
  constexpr int8_t  MaxBullets = 4;
  // fixed number of bullet "slots" some may be empty/none
  Objects::Object bullets[MaxBullets];
  uint8_t lifetimes[MaxBullets];

  void SetSpeed(Objects::Object* pBullet)
  {
    // Set the bullet's speed, X & Y speeds are -31...-6 or +6...+31 (TIMES 4)
    uint8_t bits = Objects::Random(4);
    pBullet->dX = 4*Objects::Random(6, 32) << Objects::SpeedShiftFactor;
    pBullet->dY = 4*Objects::Random(6, 32) << Objects::SpeedShiftFactor;
    if (bits & 0x01)
      pBullet->dX = -pBullet->dX;
    if (bits & 0x02)
      pBullet->dY = -pBullet->dY;
  }

 void Random(Objects::Object* pBullet, Objects::Object* pSource)
  {
    // Make a random bullet in the given slot, fired from pSource
    pBullet->type = Objects::Bullet;
    pBullet->scaleFactor = DVG::UnityScale;
    pBullet->size = 16;
    SetSpeed(pBullet);
    pBullet->X = pSource->X;
    pBullet->Y = pSource->Y;
    // Set bullet to last for 18 frames
    lifetimes[pBullet - bullets] = 18;
    pBullet->wrap = false;
  }

  void Init()
  {
    // create zero bullets
    ::memset(bullets, Objects::None, sizeof(bullets));
  }

  bool Fire(Objects::Object* pSource)
  {
    // create a random bullet fired from the pSource
    // true if fired
    Objects::Object* pBullet = Objects::GetFreeSlot(bullets, MaxBullets);
    if (pSource && pSource->type == Objects::Saucer && pBullet)
      Random(pBullet, pSource);
    return pBullet != nullptr;
  }

  void Draw()
  {
    // just paint the bullets
    Objects::Object* pBullet = bullets;
    for (int idx = 0; idx < MaxBullets; idx++, pBullet++)
      Objects::Draw(*pBullet);
  }

  void AnimationStep()
  {
    int16_t X, Y;
    // move bullets & check for collisions
    Objects::Object* pBullet = bullets;
    for (int idx = 0; idx < MaxBullets; idx++, pBullet++)
      if (Rocks::HitTest(*pBullet, X, Y))
        pBullet->type = Objects::None;
      else
      {
        // count down to expiration
        if (lifetimes[idx])
        {
          lifetimes[idx]--;
          if (!lifetimes[idx])
            pBullet->type = Objects::None;
        }
        Objects::AnimationStep(*pBullet);
      }
  }

}
