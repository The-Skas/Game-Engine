#include "Input.h"
#include <iostream>
#include "Globals.h"
#include "Component.h"
#include "Entity.h"
 
//Broadcasts the Message to all components of in the same Entity
void Input::BroadcastToComponents(Message * msg)
{
   for (std::map<unsigned, Component*>::iterator itr = inputComponents.begin(); itr != inputComponents.end(); ++itr)
      {
        Entity * entity = itr->second->GetOwner();
        //Broadcasts the Message to all compfonents of the entity
        for (unsigned int j = 0; j < entity->Components.size(); j++)
        {
          entity->Components[j]->BroadcastMessage(msg);
        }
      }
}
void Input::BroadcastMessage(Message * message)
{
  if (message->msgID == MessageID::Spawn)
  {
    CallSpawnFunction(static_cast<SpawnMessage*>(message));
  }
 // else (message->msgID == MessageID::
}
struct MouseLoc
{
  int x,y;
};
void Input::Update(float timeslice)
{
	//Handle Input Keys
	while (g_App->GetEvent(input)) {
    Message msg;
    if ((input.Type == sf::Event::MouseButtonPressed))
    {
    
    }
    else if (input.Type ==  sf::Event::MouseMoved)
    {
      std::cout << input.MouseMove.X << std::endl;
      msg.msgID = MessageID::MouseMove;
      msg.info = (void*)(&(input.MouseMove));

      BroadcastToComponents(&msg);
    }
		else if ( (input.Type == sf::Event::KeyPressed))
		{
      if (input.Key.Code == sf::Key::Escape)
      {
				CORE->GameActive = false;
        return;
      }
			std::cout << "Keycode is " << input.Key.Code << std::endl;
      
      msg.msgID = MessageID::CharacterKey;
      //Sets the key code to the messsage's void pointer
      msg.info = (void*) input.Key.Code;
			CORE->BroadcastMessage(&msg);     
			BroadcastToComponents(&msg);
		}
    
	}


};

void Input::CallSpawnFunction(SpawnMessage * msg)
{
  if (msg->type == EntityID::ParticleSystem)
  {
    Component * input = new Component;
    input->SetComponentId(CompID::Input);
    input->SetOwner(msg->owner);
    msg->components->push_back(input);
    inputComponents[msg->entid] = (input);
    //Create an input component
    ;
  }
  ;
}
std::string Input::GetName() 
{
	return 0;
};
 void Input::Initialize()
 {

 };

 Input::~Input()
 {
 };

 