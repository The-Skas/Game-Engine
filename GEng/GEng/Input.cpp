#include "Input.h"
#include <iostream>
#include "Globals.h"
#include "Component.h"
#include "Entity.h"
void Input::BroadcastMessage(Message * message)
{
  if (message->msgID == MessageID::Spawn)
  {
    CallSpawnFunction(static_cast<SpawnMessage*>(message));
  }
};
void Input::Update(float timeslice)
{
	//Handle Input Keys
	while (g_App->GetEvent(input)) {

		if ( (input.Type == sf::Event::KeyPressed))
		{
			std::cout << "Keycode is " << input.Key.Code << std::endl;
      Message msg;
      msg.msgID = MessageID::CharacterKey;
      //Sets the key code to the messsage's void pointer
      msg.info = (void*) input.Key.Code;
			CORE->BroadcastMessage(&msg);
      for (unsigned int i = 0; i < inputComponents.size(); i++)
      {
        Entity * entity = inputComponents[i]->GetOwner();
        //Broadcasts the Message to all components of the entity
        for (unsigned int j = 0; j < entity->Components.size(); j++)
        {
          entity->Components[j]->BroadcastMessage(&msg);
        }
      }
			if (input.Key.Code == sf::Key::Escape)
				CORE->GameActive = false;
      else if( input.Key.Code == sf::Key::F1)
        std::cout <<"Do nothing" << std::endl;// Do relevant full screen input
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
    inputComponents.push_back(input);
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

 