#include <Arduino.h>
#include "Game.h"
#include "DVG.h"
#include "VGROM.h"
#include "Objects.h"

namespace Objects {
  Object* GetFreeSlot(Object* pObjects, int Size)
  {
    // return a pointer to a free object in the array, or null
    Object* pObject = pObjects;
    for (int idx = 0; idx < Size; idx++, pObject++)
      if (pObject->type == Objects::None)
        return pObject;
    return nullptr;
  }

  // potentially could've used the original PRNG, see label "GetRandNum:"
  int Random(int max)
  {
    // 0 <= rnd < max
    return ::random(max);
  }

  int Random(int min, int max)
  {
    // min <= rnd < max
    return ::random(min, max);
  }

  void RandomSeed(unsigned long seed)
  {
    ::randomSeed(seed);
  }

  bool Draw(Object& object)
  {
    // draw the given object, true if drawn
    DVG::Cursor(object.X >> PositionShiftFactor, object.Y >> PositionShiftFactor, object.scaleFactor & 0x0F);
    if (object.type <= Rock3)
      DVG::Run(VGROM::Rock(object.type));
    else if (object.type == Saucer)
      DVG::Run(VGROM::Saucer());
    else if (object.type == Bullet)
      DVG::DrawDot();
    else
      return false;
    return true;
  }

  bool AnimationStep(Object& object)
  {
    // moves the object, true if moved
    if (object.type != Objects::None)
    {
      object.X += object.dX;
      object.Y += object.dY;
      bool wrappedX = true, wrappedY = true;
      if (object.X < 0)
        object.X = maxX - 1;
      else if (object.X >= maxX)
        object.X = 0;
      else
        wrappedX = false;

      if (object.Y < 0)
        object.Y = maxY - 1;
      else if (object.Y >= maxY)
        object.Y = 0;
      else
        wrappedY = false;
      if ((wrappedX || wrappedY) && !object.wrap)
        object.type = None;
      return true;
    }
    return false;
  }
}
