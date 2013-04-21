#include "EntityList.h"

EntityList * ENTLIST;
EntityList::EntityList()
{
};
void EntityList::Initialize()
{
  LastId = 0;
};

void EntityList::Update(float ts)
{
}
std::string EntityList::GetName()
{
	return "EntityList";
}
void EntityList::AddEntity(Entity *e)
{
	e->ID = LastId;
	eList.insert(std::pair<unsigned,Entity* >(LastId,e));
	LastId++; 
};

void EntityList::DestroyEntity(unsigned id)
{
	eList.erase(id);
};
void EntityList::DestroyAll()
{
	eList.clear();
};
EntityList::~EntityList()
{
	DestroyAll();
};