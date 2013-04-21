#ifndef GENG_SRC_PARTICLE_H_
#define GENG_SRC_PARTICLE_H_
#include "GraphicsComponent.h"
#include <list>
#include "State.h"

namespace GlMode  
{
enum mode
  {
    glPoints = 0x01,
    glLines  = 0x02,
    glQuads  = 0x04,
    glDraw   = 0x08,
  };
};

template <class T>
class ParticleManager;
class ParticleGroup : public GraphicsComponent
{
public:

  ~ParticleGroup();
  //Color
  float r, g, b, alpha;
  float trailAlpha;
  //Size of Trail
  unsigned int trailSize;

  float velocityX;
  float velocityY;
  State<ParticleGroup> * state;
  //List
  std::list<Transform> particleFade;
  std::list<Transform>::iterator it;
  ParticleGroup(int tempTrailSize = 15, float A = 1.0,float R = 1.0, float G = 1.0, float B = 1.0);
  //List Size
  //
  
  ParticleManager<ParticleGroup> * pParticleManager;
  virtual unsigned char getMode() 
  {
    return baseMode;
  }
  virtual void DrawGL();
  virtual void DrawPointsGL();
  virtual void DrawLinesGL() ;
  virtual void DrawQuadsGL();
  void DrawFade();

private:
  const static unsigned char baseMode = GlMode::glPoints | GlMode::glLines;

};
#endif