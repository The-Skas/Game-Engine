#include "_Math.h"

float Distance(float x1, float x2, float y1, float y2)
{
  float diffx = x1-x2;
  float diffy = y1-y2;
  float distance = diffx*diffx + diffy*diffy;
  //return std::sqrt(distance);
  return distance;
}

