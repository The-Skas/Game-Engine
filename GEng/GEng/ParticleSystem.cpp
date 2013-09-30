#include "ParticleSystem.h"
#include "RoughSketch.h"

namespace Systemstate
{
  enum Systemstates
  {
    wander,
    ocean,
    mask_ocean,
    size
  };
};
ParticleSystem::ParticleSystem()
{
  state = -1;
  
  std::string temp =  "Use the Left or Right arrow keys to cycle through.\n";
  
  effect.setString(temp);
  effect.setCharacterSize(20.0f);
  effect.setStyle(sf::Text::Bold);
  effect.setPosition(10, 10);
}
ParticleSystem::~ParticleSystem()
{
}
void ParticleSystem::ChangeState()
{
#warning Memory Leak. Issue Could be with Graphics Component Not having a deallocater.
  for (unsigned i = 0; i < vectorOfGraphics.size(); ++i)
  {
    delete vectorOfGraphics[i];
  }
  vectorOfGraphics.clear();

  ParticleManager<ParticleGroup> * temp = new ParticleManager<ParticleGroup>;
  temp->trans = this->trans;

  state = state % (Systemstate::size);
  if ( state == Systemstate::wander )
  {
    effect.setString("Wandering Particles.");
    for (unsigned i = 0; i < 100; ++i)
    {
      temp->AddParticle(new ParticleGroup(30));
    }
    temp->mode = GlMode::glLines | GlMode::glPoints;
    vectorOfGraphics.push_back(temp);
  }
  else if (state == Systemstate::ocean)
  {
    effect.setString("Ocean(Perlin Noise)");
    for (int j = 0; j < 32000; ++j)
      temp->AddParticle(new ParticleGroup(0, 1.0f, .8f, 1.0f, 1.0f));
    temp->mode =GlMode::glPoints;
    vectorOfGraphics.push_back(temp);

    //Add a wander within it
    temp = new ParticleManager<ParticleGroup>;
    temp->trans = this->trans;
    temp->AddParticle(new Water(20));
    temp->mode = GlMode::glDraw;
    
    vectorOfGraphics.push_back(temp);

  }
  else if (state==Systemstate::mask_ocean)
  {
    vectorOfGraphics.push_back(new RoughSketch);
    effect.setString("Ocean with Mask");
    for (int j = 0; j < 32000; ++j)
      temp->AddParticle(new ParticleGroup(0, 1.0f, .8f, 1.0f, 1.0f));
    temp->mode =GlMode::glPoints;
    temp->masked = true;
    vectorOfGraphics.push_back(temp);

    //Add a wander within it
    GraphicsComponent * water = new Water(20);
    water->trans = this->trans;
    water->masked = true;
    vectorOfGraphics.push_back(water);
  }
  
}
void ParticleSystem::BroadcastMessage(Message * message)
{
  //Recieve inputs for the ParticleSystem
  //Intialise the relevant particleManagers for each differing input
  int key = (size_t)(message->info);
  if (message->msgID == MessageID::CharacterKey)
  {
    if (key == sf::Keyboard::Right)
    {
      //Go to next manager state with its own intialises
      ++state;
      //Call the function that intialises depending on what state.
      ChangeState();
    }
    else if (key == sf::Keyboard::Left)
    {
      --state;//Go to previous state
      //Call the function that intialises depending on what state.
      ChangeState();
    }
  }
  else if (message->msgID == MessageID::MouseMove)
  {
    //Broadcast to all GraphicComponents;
    for (unsigned i = 0; i < vectorOfGraphics.size(); ++i)
    {
      vectorOfGraphics[i]->BroadcastMessage(message);
    }
  }
}

void ParticleSystem::DrawGL()
{
  for (unsigned i = 0; i < vectorOfGraphics.size(); ++i)
  {

    vectorOfGraphics[i]->DrawGL();
  }
  g_App->draw(effect);
}

