#ifndef GENG_SRC_PARTICLEWANDER_H_
#define GENG_SRC_PARTICLEWANDER_H_
#include "State.h"
//template <class P>
class ParticleGroup;
class ParticleWander : public State<ParticleGroup>
{
public:
  void enter(ParticleGroup * type);

  void execute(ParticleGroup * type);

  void exit(ParticleGroup * type);

  static int decr;
};

#endif  
