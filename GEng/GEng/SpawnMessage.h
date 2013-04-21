#ifndef GENG_SRC_SPAWNMESSAGE_H_
#define GENG_SRC_SPAWNMESSAGE_H_
#include "Messages.h"
#include "EntitySheet.h"
#include <vector>
class Component;
class Entity;
class Transform;
class SpawnMessage : public Message
{
public:
  SpawnMessage(){};
  Transform* trans;
  EntityID::EntityType type;
  std::vector<Component *>* components;
  Entity *owner;
  unsigned int entid;
  //Used to pass additional info

  ~SpawnMessage(){};
};
#endif 