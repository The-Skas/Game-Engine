
#include "ParticleWander.h"
#include "ParticleManager.h"
#include "_Math.h"
//#include "ParticleGroup.h"
//use #include "ParticleManager.h"
//if you will be using the backpointer "owner"
int ParticleWander::decr = 0;
void ParticleWander::enter(ParticleGroup * ParticleGroup)
{
 // ParticleGroup->velocityX = sf::Randomizer::Random(-1.0f, 1.0f);
 // ParticleGroup->velocityY = sf::Randomizer::Random(-1.0f, 1.0f);
 // ParticleGroup->velocityX = 0.5;
  //ParticleGroup->velocityY = 0.5;
}
/*ParticleWander execute
The following code causes the ParticleGroup to steer. Thanks to programming source AI by mat buckland.
It basically locates the next position using the current velocity, and from there, randomizes to a location.
This creates a smoooth steering, rather then a constant chaos of particles
*/
 void ParticleWander::execute(ParticleGroup * ParticleGroup)
{
  //                                          :^: This value Expands the radius of roaming
  //                                                                            :^: These values controls the fluidity of changing direction

  ParticleGroup->velocityX =ParticleGroup->velocityX * 0.99f + RandRange(-.25f, .25f);
  ParticleGroup->velocityY =ParticleGroup->velocityY * 0.99f + RandRange(-.25f, .25f);

 
}
 void ParticleWander::exit(ParticleGroup * ParticleGroup)
{
  //ParticleGroup->pParticleManager->DeleteParticle(ParticleGroup->pParticleManager->mapParticles.begin()->second);
};