#ifndef GENG_SRC_PARTICLEMANAGER_H_
#define GENG_SRC_PARTICLEMANAGER_H_
#include "ParticleGroup.h"
#include "Entity.h"
#include <map>
#include "SpawnMessage.h"
#include "ParticlesExpand.h"
#include "ParticleWander.h"
#include "ParticleWater.h"
#include "Water.h"
#include "Graphics.h"
/***********************
//The ParticleGroup Manager//
*************************
/* The ParticleGroup manager was created to manage thousands of particles of a templated type. It was mainly created
// to group all the particles in as little glBegin calls as possible. A ParticleGroup is added from the graphics sys-
// tem. Each ParticleGroup will be an entity, though it wont be in the main Entity map t to prevent the list size growing 
// by the thousands. Which is why I, have created a map within this class, that stores a an ID along side a ParticleGroup.
/*
//glMode..
//This will be a flag set by the ParticleGroup Template, depending on what is checked. the corresponding function will be traversed.

/*glMode defined in ParticleGroup.h//
enum glMode
{
  glPoints = 0x01,
  glLines  = 0x02,
  glQuads  = 0x04,
}; 
*/
template <class T>
class ParticleManager : public GraphicsComponent
{
public:
  //A ParticleGroup Template is automatically set on declaration.
  ParticleGroup * particleTemplate;
  ParticleManager();
  ~ParticleManager();

  State<ParticleGroup> * state;
  //The glMode
  unsigned char mode;

  //ID
  unsigned int  particleID;
  //Adds a ParticleGroup
  ParticleGroup * AddParticle(ParticleGroup * temp);
  
  void DeleteParticle(ParticleGroup * particleGroup);
  //Virtual function of GraphicsComponent to be called from Graphics.cpp
  void DrawGL();

  void ChangeState();
 
  void BroadcastMessage(Message * msg);

  //A list of all the transforms should be included.
  std::map<unsigned int, ParticleGroup *> mapParticles;
  //The ParticleGroup Manager will draw both the GL_LINES, the GL_POINTS, the GL_QUADS, or any other type.
  //Each will be called in a seperate glBegin()
};

template <class T>
ParticleManager<T>::ParticleManager()
{
  ParticleGroup * particleGroup = new T;
  //Rain or of type Squares, or whatever

  //Gets the flags for the glBegin attributes ie: GL_POINTS, GL_LINES
  mode = particleGroup->getMode();
  particleTemplate = particleGroup;
  particleTemplate->pParticleManager = this;
  mapParticles.clear();
  particleID = 0;
  state = new ParticleWander;
  sf::Randomizer::GetSeed();
}
template <class T>
inline ParticleManager<T>::~ParticleManager()
{
  for (std::map<unsigned int, ParticleGroup*>::iterator itr = mapParticles.begin(); itr != mapParticles.end(); ++itr)
  {
    DeleteParticle(itr->second);
  }
  delete particleTemplate;
  delete state;
};
template <class T>
//                                  call(  new      Class  );
ParticleGroup * ParticleManager<T>::AddParticle(ParticleGroup * tempParticle)
{
  Entity * particleGroup = new Entity;
  particleGroup->ID = particleID;
  ++particleID;
  particleGroup->trans.position.x = this->trans->position.x;
  particleGroup->trans.position.y = this->trans->position.y;

  

  tempParticle->SetOwner(particleGroup);
  tempParticle->trans = &(particleGroup->trans);
  tempParticle->pParticleManager = this;
  
  particleGroup->AddComponent(tempParticle);
  mapParticles[particleGroup->ID] = tempParticle;
  //(mapParticles[0])->DrawPointsGL();
  
  SpawnMessage spawn;
  spawn.trans = &(particleGroup->trans);
  spawn.msgID = MessageID::Spawn;
  spawn.type = EntityID::ParticleGroup;
  spawn.owner = particleGroup;
  spawn.components = &(particleGroup->Components);
  
  

 

  CORE->BroadcastMessage(&spawn);
  
  return tempParticle;
}

template <class T>
void ParticleManager<T>::DeleteParticle(ParticleGroup * particleGroup)
{
  //could there be a possible memory leak?
  int tempID =  particleGroup->GetOwner()->ID;


  delete particleGroup->GetOwner();
  delete particleGroup;
 // mapParticles.erase(mapParticles.find(tempID));


}
template <class T>
void ParticleManager<T>::DrawGL()
{
  if (mapParticles.size() == 0)
    return;
  float width = g_App->GetWidth()/800.0f;
  float height = g_App->GetHeight()/600.0f;

 
  //Flag Check
  //mapParticles[0]->b;
  state->exit(mapParticles.begin()->second);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  
  for (std::map<unsigned int, ParticleGroup *>::iterator itr = mapParticles.begin(); itr != mapParticles.end(); itr++)
  {
    state->execute(itr->second);
  }
  if (mode &  GlMode::glDraw)
  {
    for (std::map<unsigned int, ParticleGroup*>::iterator itr = mapParticles.begin(); itr !=  mapParticles.end(); ++itr)
      {
        itr->second->DrawGL();
      }
  }
  if (mode & GlMode::glLines)
  {
    glBegin(GL_LINES);
      for (std::map<unsigned int, ParticleGroup*>::iterator itr = mapParticles.begin(); itr !=  mapParticles.end(); ++itr)
      {
        itr->second->DrawLinesGL();
      }
    glEnd();
  }
  if (mode & GlMode::glPoints)
  {
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (std::map<unsigned int, ParticleGroup*>::iterator itr = mapParticles.begin(); itr != mapParticles.end(); ++itr)
    {
      itr->second->DrawPointsGL();
      itr->second->trans->position.x += itr->second->velocityX;
      itr->second->trans->position.y += itr->second->velocityY;
      
    }
    glEnd();
  }

  if (mode & GlMode::glQuads)
  {
    glBegin(GL_QUADS);
    for (std::map<unsigned int, ParticleGroup*>::iterator itr = mapParticles.begin(); itr != mapParticles.end(); ++itr)
       itr->second->DrawQuadsGL();
    glEnd();
  
  }
  
}

template <class T>
void ParticleManager<T>::BroadcastMessage(Message *msg)
{
  if (msg->msgID == MessageID::CharacterKey)
  {
    if (mapParticles.size() == 0 )
      return;
    if ((int)msg->info == sf::Key::Right)
    {
      State<ParticleGroup>* temp = state;
      state->exit(particleTemplate);
      state = new ParticleWater;
      delete temp;
      state->enter(particleTemplate);
      mode = GlMode::glLines | GlMode::glPoints;
    }
    else if ((int)msg->info == sf::Key::Down)
    {
      this->state->exit(particleTemplate);
      State<ParticleGroup>* temp = state;
      state = new ParticleWander;
      if (state != NULL)
        delete temp;
      state->enter(particleTemplate);

      mode = mode | GlMode::glLines | GlMode::glPoints;
    }
    else if ((int)msg->info == sf::Key::Left)
    {
       
       //AddParticle(new Water(150));

      // NonTexInstances.push_back(new Water(150));
       mode = 0;
       mode = mode |GlMode::glQuads|GlMode::glPoints ;

       this->state->exit(particleTemplate);
       State<ParticleGroup>* temp = state;

       state = new ParticleWander;
       delete temp;
    }
  };
};
#endif