#ifndef GENG_SRC_PARTICLESYSTEM_H_
#define GENG_SRC_PARTICLESYSTEM_H_
#include "GraphicsComponent.h"
#include <vector>
#include "ParticleManager.h"
//c//lass ParticleGroup;
class ParticleSystem : public GraphicsComponent
{
public:
  ParticleSystem();

  ~ParticleSystem();
  void BroadcastMessage(Message * message);
  //a virtual function for all Graphics Components
  void DrawGL();
  //Changing 
  void ChangeState();
  //Or it would need a function to initilaise different states depending on an input

  //On input , initalise the appropriate ParticleManagers to be used.
private:
  int state;
  std::vector<ParticleManager<ParticleGroup>*> vectorOfManagers;
  sf::String effect;
};
#endif