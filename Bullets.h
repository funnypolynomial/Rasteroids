#pragma once

namespace Bullets
{
  // Bullets fired by Saucer
  void Init();
  bool Fire(Objects::Object* pSource);
  void Draw();
  void AnimationStep();
};
