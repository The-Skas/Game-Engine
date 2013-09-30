#include "ParticleGroup.h"
#include "Entity.h"
#include <iostream>
#include "ParticleWander.h"
#include "ParticlesExpand.h"
//CAUTION:
//Increasing trail size, decreases FPS drastically,

ParticleGroup::ParticleGroup(int tempTrailSize, float A,float R , float G, float B )
  {
    r=(float)rand()/(float)RAND_MAX;g=(float)rand()/(float)RAND_MAX;b=(float)rand()/(float)RAND_MAX; alpha = 1.0; trailSize = tempTrailSize; trailAlpha = ((float)A)*0.3f;
    velocityX = 0;
    velocityY = 0;
    state = new ParticleWander;
    state->enter(this);
  }

ParticleGroup::~ParticleGroup()
{
  delete state;

}
void ParticleGroup::DrawGL()
{
  glBegin(GL_POINTS);
    DrawPointsGL();
  glEnd();

  glBegin(GL_LINES);
    DrawLinesGL();
  glEnd();

}
void ParticleGroup::DrawLinesGL()
{
  if (particleFade.size() > trailSize)
    particleFade.pop_back();

  DrawFade();

  particleFade.push_front(*trans);
  
}

void ParticleGroup::DrawPointsGL()
{
    //do this
    glColor4f(r, g, b, alpha);
    glVertex2f(trans->position.x, trans->position.y);
}

void ParticleGroup::DrawQuadsGL()
{


}
// DrawFade()
/*
//This function handles the drawing of the fading particles.
//It iterates reversely through the list as to draw the least alpha
//ParticleGroup first.
*/
void ParticleGroup::DrawFade()
{
  if (particleFade.size() == 0)
    return;
  
  //The trailSize variable is used over the .size()
  float i =  trailAlpha/trailSize;
  float decrRate = i;
  
  //*When using Iterators, if you wish to reverse iterate, do not exchange begin / end
  //Instead, use the rbegin / rend.
  it = particleFade.begin();
  glVertex2f(trans->position.x, trans->position.y);
  glVertex2f(particleFade.front().position.x, particleFade.front().position.y);
  glColor4f(r, g, b, trailAlpha);
  glVertex2f(particleFade.front().position.x, particleFade.front().position.y);

                    //Have to convert it to an iterator type first
  for (++it; it != (std::list<Transform>::iterator)particleFade.end();)
  {
    glVertex2f(it->position.x, it->position.y);
    i += decrRate;
    glColor4f(r, g, b, trailAlpha-i);
    glVertex2f(it->position.x, it->position.y);
    ++it;
  }
  glVertex2f(particleFade.back().position.x, particleFade.back().position.y);
};

