#ifndef GAMELOGIC
#define GAMELOGIC

#include "SystemStructure.h"
#include "EntitySheet.h"
#include "Entity.h"
class SpawnMessage;
class GameLogic : public System
{
public:
	 void BroadcastMessage(Message* message);

	//Updates based on time
	 void Update(float timeslice);	

	//The name of the system
	 std::string GetName();	

	//System initialization
	 void Initialize();

   Entity* SpawnEntity(EntityID::EntityType eType, float x, float y);
	 
   void CallSpawnFunction(SpawnMessage * msg);
	~GameLogic();
};

#endif
