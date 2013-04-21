#ifndef SYSTEMSTRUCTURE
#define SYSTEMSTRUCTURE

#include "Messages.h"
#include <string>

//Template (Interface) for all systems (graphics, physics, etc..) with basic message, update
//and initialize functionality
class System
{
public:
	//How the System handles a message
	virtual void BroadcastMessage(Message* message) {};

	//Updates based on time
	virtual void Update(float timeslice) = 0;	

	//The name of the system
	virtual std::string GetName() = 0;	

	//System initialization
	virtual void Initialize(){};
		
	//Destructor
	virtual ~System(){}						
};

#endif