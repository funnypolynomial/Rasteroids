#pragma once
namespace Objects
{
  // Common object (Saucer, Rock, Bullet) code
  constexpr uint8_t  PositionShiftFactor = 3;     // positions are 8* beam coords
  constexpr uint8_t  SpeedShiftFactor = 1;        // increase speed to allow for our frame rate
  constexpr uint8_t  SplashSpeedShiftFactor = 3;  // increase splash speed
  
  enum Type
  {
    Rock0  = 0,
    Rock1  = 1,
    Rock2  = 2,
    Rock3  = 3,
    Saucer = 10,
    Bullet = 20,
    None   = 0xFF
  };

  constexpr int16_t maxX = DVG::beamWidth  << PositionShiftFactor;
  constexpr int16_t maxY = DVG::beamHeight << PositionShiftFactor;

  struct Object
  {
    uint8_t type = None;
    uint8_t scaleFactor = 0x00;   // 0xPQ, P is 0/1/2 for /1, /2 or /4; Q is scale passed to DCG
    int16_t X = 0, Y = 0;         // these are stored as 8* beam coords
    int16_t dX = 0, dY = 0;       // speed
    uint8_t size = 0;
    bool wrap = true;             // wrap around the screen else vanish at the edge
  };

  Object* GetFreeSlot(Object* pObjects, int Size);
  int Random(int max); // 0 <= rnd < max
  int Random(int min, int max); // min <= rnd < max
  void RandomSeed(unsigned long seed);

  bool Draw(Object& data);
  bool AnimationStep(Object& data);
};
