#ifndef GENG_SRC_MATH_H_
#define GENG_SRC_MATH_H_
#include <cmath>
#include <iostream>

//such that the vector would be
//X2Y2 -> X1Y1
inline float Distance(float diffx, float diffy)
{
  float distance = diffx*diffx + diffy*diffy;
  return std::sqrt(distance);
};


inline float DotProduct(float x1, float y1, float x2, float y2)
{
  return x1*x2 + y1*y2;
};
inline float LERP(float a, float b, float x)
{
  float ft = x * 3.1415927f;
	float f = (1 - std::cos(ft)) * .5f;
  return (a*(1-f) + b*f);
};

inline float RandRange(float startRange, float endRange)
{
  float rndNum =(float)rand()/(float)RAND_MAX;
  
  //calculate range difference
  float rangeDiff = endRange  - startRange;
  
  rndNum *= rangeDiff;
  
  rndNum += startRange;
  
  return rndNum;
}
#endif