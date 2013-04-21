#include "ParticlesExpand.h"
#include "ParticleManager.h"
void ParticlesExpand::enter(ParticleGroup * particleGroup)
{
  //The particles will organize in a circle along the circumference of a circle
  //I would need the radius so each ParticleGroup.
  radius = 100;
  angle = 0;
  angleIncrRate;
  originX = particleGroup->pParticleManager->trans->position.x;
  originY = particleGroup->pParticleManager->trans->position.y;
  
  std::map<unsigned int ,ParticleGroup*> * mapParticles = &(particleGroup->pParticleManager->mapParticles);
  angleIncrRate = 360.0f/(float)mapParticles->size();
  /*for(int i = 0; i < mapParticles->size(); i++)
  {
    (*mapParticles)[i]->velocityX = std::cos(this->angle);
    (*mapParticles)[i]->velocityY = std::sin(this->angle);
    (*mapParticles)[i]->trans->position.x = originX + std::cos(this->angle) * this->radius;
    (*mapParticles)[i]->trans->position.y = originY + std::sin(this->angle) * this->radius;
    angle += angleIncrRate;
  }*/
  for (std::map<unsigned int, ParticleGroup*>::iterator itr = mapParticles->begin(); itr != mapParticles->end(); ++itr)
  {
    //Vector Subtraction: Origin - ParticleGroup position 
    itr->second->velocityX = originX - itr->second->trans->position.x;
    itr->second->velocityY = originY - itr->second->trans->position.y;

    //Vector Unit
    float unitVector = itr->second->velocityX * itr->second->velocityX + itr->second->velocityY * itr->second->velocityY;
    unitVector = std::sqrt(unitVector);

    if(unitVector >= radius)
      ;//do nothing
    else
    {
      unitVector *= -1.0f;
    }

    itr->second->velocityX /= unitVector;
    itr->second->velocityY /= unitVector;
  }

}
//avoid the 's or s at the end of plural words ie "Particles" or "ParticleGroup" !:S
void ParticlesExpand::execute(ParticleGroup * particleGroup)
{
  float distx = originX - particleGroup->trans->position.x;
  float disty = originY - particleGroup->trans->position.y;
  float dist =  distx * distx + disty*disty;
  //the acctual distance would be sqrt(dist) though as its computationally expensive, ill square the radius.
  //float rloc = sf::Randomizer::Random(1.0f, 1.5f);
  if ((dist < ((radius*radius) + radius*2.0f) && dist > (radius*radius - radius*2.0f)))
  {
      particleGroup->velocityX = 0;
      particleGroup->velocityY = 0;

  }

}

void ParticlesExpand::exit(ParticleGroup * particleGroup)
{
}
