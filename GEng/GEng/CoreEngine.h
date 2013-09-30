#ifndef COREENGINE
#define COREENGINE
#include "SystemStructure.h"
#include <SFML/System.hpp>
#include <vector>
//The core manages all the systems in the game. Updating them, routing messages, and
//destroying them when the game ends.
class CoreEngine
{
public:
	CoreEngine();
	~CoreEngine();

	//Update all the systems until the game is no longer active.
	void GameLoop();

	//Destroy all systems in reverse order that they were added.
	void DestroySystems();

	//Broadcasts a message to all systems.
	void BroadcastMessage(Message* m);

	//Adds a new system to the game.
	void AddSystem(System* system);

	//Initializes all systems in the game.
	void Initialize();

	//Is the game running (true) or being shut down (false)?
	bool GameActive;


private:
	//Tracks all the systems the game uses
	std::vector<System*> Systems;
	
  //Time functionality using sfml library
  sf::Clock clock;

  float LastTime;
  float currentTime;
  float dt;
};

/*///Message to tell the game to quit
class MessageQuit : public Message
{
public:
	MessageQuit() : Message(Mid::Quit) {};
};

///Signals all systems to activate or deactivate the display of debug data.
class ToggleDebugDisplay : public Message
{
public:
	bool DebugActive;
	ToggleDebugDisplay(bool debugActive)
		: Message(Mid::ToggleDebugInfo) , DebugActive(debugActive) {};
};*/

//A global pointer to the instance of the core

#endif