#ifndef GENG_SRC_PARTICLESEXPAND_H_
#define GENG_SRC_PARTICLESEXPAND_H_
#include "State.h"
//template <class P>
class ParticleGroup;
class ParticlesExpand : public State<ParticleGroup>
{
public:
  void enter(ParticleGroup * type);

  void execute(ParticleGroup * type);

  void exit(ParticleGroup * type);

  float radius;

  float angle;

  float angleIncrRate;

  float originX, originY;
};
#endif GENG_SRC_PARTICLESEXPAND_H_