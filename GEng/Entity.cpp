#include "Entity.h"


void Entity::AddComponent(Component* c)
{
  Components.push_back(c);
}

void Entity::DeleteComponent(Component * c)
{
  delete c;
}

Entity::~Entity()
{
}