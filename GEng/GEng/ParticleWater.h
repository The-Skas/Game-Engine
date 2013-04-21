#ifndef GENG_SRC_PARTICLEWATER_H_
#define GENG_SRC_PARTICLEWATER_H_
#include "State.h"

class ParticleGroup;

//Typing class ParticleManager<T> would be an error;
template <class t>
class ParticleManager;
class ParticleWater : public State<ParticleGroup>
{
public:

  void enter(ParticleGroup * ParticleGroup);

  void execute(ParticleGroup * ParticleGroup);

  void exit(ParticleGroup * ParticleGroup);

  void AddWater();

  float size;

  float radius;

  ParticleManager<ParticleGroup> * p_manager;


};

#endif