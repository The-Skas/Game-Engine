#ifndef GENG_SRC_GRAPHICS_H_
#define GENG_SRC_GRAPHICS_H_
#include "SystemStructure.h"
#include <SFML\Graphics.hpp>
#include "ParticleManager.h"
#include "SpawnMessage.h"

//MODELS that the instances will use
class OurImage
{
public:

  sf::Image sfImage;
  EntityID::EntityType eType;
  GLuint texture;
};


class Graphics : public System
{

public:

  bool fullscreen;


  void BroadcastMessage(Message* message);

  //Updates based on time
  void Update(float timeslice);	

  //The name of the system
  std::string GetName();	

  //System initialization
  void Initialize();
		
  //Destructor
  ~Graphics();	
  void CallSpawnFunction(SpawnMessage* spawn);

  void ResizeScreen(int width, int height);

private:
	sf::RenderWindow App;

  //Images used by MODEL
  std::vector<OurImage> Models;
    
  //Objects for INSTANCES of the MODEL

 
  
};
 extern std::map<unsigned,GraphicsComponent*> NonTexInstances;
 extern std::map<unsigned,GraphicsComponent*> TexInstances;
#endif