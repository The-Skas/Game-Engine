#ifndef COMPONENT
#define COMPONENT
//#include "EntitySheet.h"
#include "Messages.h"

namespace CompID // Message id
{
  enum ComponentID
  {
    Graphics,
    Physics,
    Input,
    ParticleGroup,
  };
}

class Entity;
class Component
{
public:
  Component(){};
  virtual ~Component(){};
  //static float scrnWidth;
  //static float scrnHeight;
	//*
	//virtual void Intialize(){};
	virtual void BroadcastMessage(Message* message);
	//virtual unsigned short GetType() { return cid; }
  void                SetComponentId(CompID::ComponentID cid){this->cid = cid;};
  CompID::ComponentID GetComponentID() { return cid;}

  //Shouldnt this be handled by the entity?
  /*void                 SetEntityType(EntityID::EntityType type) { this->type;};
  EntityID::EntityType GetEntityType() { return this->cid;};*/

  void     SetOwner(Entity * e) { owner = e;}
  Entity * GetOwner() {return owner;}
private:
  CompID::ComponentID cid;
  //EntityID::EntityType type;
	Entity *owner;
};
//float Component::scrnHeight = 1;
//float Component::scrnWidth = 1;
#endif