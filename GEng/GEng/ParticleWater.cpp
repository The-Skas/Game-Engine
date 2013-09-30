#include "ParticleWater.h"
#include "ParticleManager.h"
#include "_Math.h"

#define MAGNETIC_SCALE 0.025f




void ParticleWater::AddWater()
{
  ParticleGroup* temp = p_manager->AddParticle(new ParticleGroup(0));
  float rnd = RandRange(0.5f, 1.0f);
  temp->r = rnd; temp->g =rnd; temp->b = 1.0f; temp->alpha = 1.0f;
  //temp->trans->position.x += sf::Randomizer::Random(-(int)(std::sqrt(size)*radius/2), 0);
  temp->trans->position.y += -150;
  temp->velocityX = RandRange(-0.25f, .5f);
  temp->velocityY = -1.0f;

  float sqrt;
  sqrt = std::sqrt(temp->velocityX * temp->velocityX + temp->velocityY * temp->velocityY);
}
void ParticleWater::enter(ParticleGroup * particleGroup)
{

 radius = 100;
 size = 300;
 glPointSize(3);
 p_manager = particleGroup->pParticleManager;

 int mapsize = p_manager->mapParticles.size();
 for (std::map<unsigned int, ParticleGroup *>::iterator itr = p_manager->mapParticles.begin(); itr != p_manager->mapParticles.end(); itr++ )
 {
   p_manager->DeleteParticle(itr->second);
   itr->first;
 }
 p_manager->mapParticles.clear();
// p_manager->mapParticles.clear();
 p_manager->AddParticle(new Water(20));
  // AddWater();



}


void ParticleWater::execute(ParticleGroup * particleGroup)
{
  float diffx, diffy,  forcey, forcex;

  float distance;
  forcex = 0; forcey = 0;
  for (std::map<unsigned int, ParticleGroup*>::iterator itr =  p_manager->mapParticles.find((particleGroup->GetOwner()->ID)); itr != p_manager->mapParticles.end(); itr++)
  {
    if (particleGroup->GetOwner()->ID != itr->first)
    {
      //How to Perform a Magnetic effect, which water has.
      //For each ParticleGroup, check the distance between itself and any other available ParticleGroup.
      diffx = itr->second->trans->position.x - particleGroup->trans->position.x;
      diffy = itr->second->trans->position.y - particleGroup->trans->position.y;

      distance = Distance(diffx, diffy);
      //if distance is greater then magnetic radius
      if (distance == 0.0f )
      {
        particleGroup->trans->position.x += 0;
        particleGroup->trans->position.y += 0;
        continue;
      }
      //else if distance is less or equal then magnetic radius
      else if (distance <= radius)
      {
        forcex += diffx/distance;
        forcey += diffy/distance;
      }
        //manipulate particles velocityX/Y to pull the current force towards the center.
    }
  }
  float forceM = Distance(forcex, forcey);
  if (forceM == 0)
  {
    particleGroup->velocityY +=0.05f;
    return;
  }
  distance = Distance(particleGroup->velocityX, particleGroup->velocityY);
  particleGroup->velocityX += forcex/forceM*MAGNETIC_SCALE;
  particleGroup->velocityY += forcey/forceM*MAGNETIC_SCALE + 0.05f;

}

void ParticleWater::exit(ParticleGroup * particleGroup)
{
  /* if (p_manager->mapParticles.size() < 250)
  {
    AddWater();
  }
   else
   {
     //TODO: This is causing the flickering of lines. Check out why.
     p_manager->mapParticles.erase(p_manager->mapParticles.begin());
   }*/
}