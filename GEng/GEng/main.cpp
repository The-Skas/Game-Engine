#include "CoreEngine.h"
#include "Graphics.h"
#include "Input.h"
#include "EntityList.h"
#include "GameLogic.h"
int main(void)
{
  //Create the core engine which manages all the systems that make up the game
	CoreEngine* engine = new CoreEngine;
	ENTLIST = new EntityList();
  //Add Entity List

  //For setting the engines later on
	engine->AddSystem(ENTLIST);
  engine->AddSystem(new Graphics);
  engine->AddSystem(new Input);
  engine->AddSystem(new GameLogic);
  engine->Initialize();

  //active window?

  //Run the game
	engine->GameLoop();


  //Handle Destruction of all objects
  //here

  //Delete all the systems
  engine->DestroySystems();

  //Delete the engine itself
  delete engine;

  //Game over, application will now close
  return 0;
}