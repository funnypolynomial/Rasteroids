#pragma once

namespace Rocks
{
  // The Rocks/Asteroids
  void InitWave();
  void Draw();
  void AnimationStep();
  bool HitTest(Objects::Object& obj, int16_t& X, int16_t& Y);

  void Splash(int y, int dy);
};
