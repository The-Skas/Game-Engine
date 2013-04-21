#ifndef GENG_SRC_WATER_H_
#define GENG_SRC_WATER_H_
#include "ParticleGroup.h"
#include "PerlinNoise.h"
#define MAX_SIZE 1000
struct color4
{
  float r,g,b,a;
};
class Water : public ParticleGroup
{
public:
 Water(int size);
 ~Water();
  float coordincr;
  float angleYincr;

 void glColor4Wrap(color4 var);
 unsigned char getMode()
 {
   return baseMode;
 };

 void DrawGL();
 void DrawPointsGL();
 void DrawLinesGL();
 void DrawQuadsGL();

 PerlinNoise * perlin;
private:
  float angle;
  int size;
  color4 color[MAX_SIZE][MAX_SIZE][4];
  const static unsigned char baseMode = GlMode::glPoints | GlMode::glQuads;
};

#endif