#include "SystemStructure.h"
#include <SFML\Window.hpp>
#include <map>
#include "SpawnMessage.h"
class Input : public System
{

public:
	 void BroadcastMessage(Message* message);

	//Updates based on time
	 void Update(float timeslice);	

	//The name of the system
	 std::string GetName();	

	//System initialization
	 void Initialize();
		
	//Destructor
	 ~Input();

   
   //Need to store a list of component inputs. Each component will be able to broadcast a message to their systems. Does this mean.
   //hmmm Yes it does. I traverse all components that are input related and send the input recieved to them.
   void CallSpawnFunction(SpawnMessage * msg);

   void BroadcastToComponents(Message * msg);
private:
	sf::Event input;
  unsigned id;
  std::map<unsigned,Component*> inputComponents;
};

