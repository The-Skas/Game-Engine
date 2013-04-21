#include "GameLogic.h"
#include "EntityList.h"
#include "Globals.h"
#include <iostream>
#include "SpawnMessage.h"
#include "PerlinNoise.h"
void GameLogic::BroadcastMessage(Message * message)
{
  //if (message->msgID == MessageID::Spawn)
    
}

double angle = 0;
void GameLogic::Update(float timeslice)
{
  //std::cout << ENTLIST->GetSize();
  //ENTLIST->eList[0]->Components.
  for(int i = 0; i < ENTLIST->GetSize(); i++)
  {
    ENTLIST->eList[i]->Update();
  }
  angle += 0.1;
}
std::string GameLogic::GetName() 
{
	return 0;
};

void GameLogic::Initialize()
{
  double angInc = 360.0/1000.0;
  //SpawnEntity(EntityID::ParticleManager, 400, 300);
  SpawnEntity(EntityID::ParticleSystem, 400, 300);
  SpawnEntity(EntityID::Icecream, 0, 0);
  //ENTLIST->AddEntity(new PerlinNoise(40));
  for (int i =0; i < 1000; ++i)
  {
    //SpawnEntity(EntityID::ParticleGroup, 400+std::cos(angle)*150, std::sin(angle)*150+250);
    angle += angInc;
  }
  angle = 0;
};

GameLogic::~GameLogic()
{
};



Entity* GameLogic::SpawnEntity(EntityID::EntityType eType, float x, float y)
{

  Entity* e = new Entity;
  ENTLIST->AddEntity(e);
  e->trans.position.x = x;
  e->trans.position.y = y;
  e->trans.rotation = 0;
  
  SpawnMessage spawn;
  spawn.msgID = MessageID::Spawn;
  spawn.trans = &(e->trans);
  spawn.components = &(e->Components);
  spawn.type = eType;
  spawn.owner = e;
  spawn.entid = e->ID;
  spawn.info = (void*) NULL;
  std::cout << (*spawn.trans).position.x << std::endl;

  std::cout << e->trans.position.x << std::endl;

  CORE->BroadcastMessage(&spawn);

  return e;
  
};

void GameLogic::CallSpawnFunction(SpawnMessage * spawn)
{
 // if (spawn->type == EntityID::ParticleManager)
  //  ;

}