#ifndef GENG_SRC_PERLINNOISE_H_
#define GENG_SRC_PERLINNOISE_H_
#include "Globals.h"
#include "EntityList.h"
#include "Math.h"

#define RATE_OF_CHANGE 0.5f
class PerlinNoise : public Entity
{
public:
  PerlinNoise(int size, float scales = 1.0f)
  {
    width = length = size;
    rateofchange = scales;
    Initialise();
  };

  ~PerlinNoise();
  float rateofchange;
  unsigned int width;
  unsigned int length;
  float *** rateOfChange;
  float *** RandomVectors;
  void Update();
  void Initialise();
  float Perlin2D(float x, float y);
};


#endif