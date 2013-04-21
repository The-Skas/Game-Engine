#include "CoreEngine.h"
#include "Globals.h"
#include <iostream>
CoreEngine::CoreEngine()
{
  Clock.Reset();
	GameActive = true;
	CORE = this; //Set the global pointer
}

CoreEngine::~CoreEngine()
{
	//Nothing for the destructor to do
}

void CoreEngine::Initialize()
{
	for (unsigned i = 0; i < Systems.size(); ++i)
		Systems[i]->Initialize();
}

void CoreEngine::GameLoop()
{
	//Initialize the last time variable so our first frame
	//is "zero" seconds (and not some huge unknown number)
	LastTime = Clock.GetElapsedTime();
  LastTime = Clock.GetElapsedTime();
	while (GameActive)
	{
		//Get the current time in milliseconds
		currentTime = Clock.GetElapsedTime();
		//Convert it to the time passed since the last frame (in seconds)
		dt = currentTime - LastTime;
		//Update the when the last update started
		

    //std::cout << "The time: " << currentTime << std::endl;
		//Update every system and tell each one how much
		//time has passed since the last update
    if (dt > 0.01)
    {
      LastTime = currentTime;
		  for (unsigned i = 0; i < Systems.size(); ++i)
			Systems[i]->Update(dt);

    }
    //std::cout << 1/(Clock.GetElapsedTime()-LastTime) << std::endl;
	}

}

void CoreEngine::BroadcastMessage(Message* message)
{
	//The message that tells the game to quit
	if (message->msgID == MessageID::Quit)
		GameActive = false;

	//Send the message to every system--each
	//system can figure out whether it cares
	//about a given message or not
	for (unsigned i = 0; i < Systems.size(); ++i)
		Systems[i]->BroadcastMessage(message);
}

void CoreEngine::AddSystem(System* system)
{
	//Add a system to the core to be updated
	//every frame
	Systems.push_back(system);
}

void CoreEngine::DestroySystems()
{			
	//Delete all the systems in reverse order
	//that they were added in (to minimize any
	//dependency problems between systems)
	for (unsigned i = 0; i < Systems.size(); ++i)
	{
		delete Systems[Systems.size()-i-1];
	}
}