#ifndef ENTITY
#define ENTITY

#include "Transform.h"
#include "Component.h"
#include <vector>
class Entity
{
public:
	friend class EntityList;
  Entity(){};
  ~Entity();

	//Adds a component, wether it be a body (physics), or sprite (Graphics)
  void AddComponent(Component* c);

  void DeleteComponent(Component * c);
  virtual void Update() {};
  unsigned ID;
  Transform trans;
  std::vector<Component*> Components;
};
#endif 