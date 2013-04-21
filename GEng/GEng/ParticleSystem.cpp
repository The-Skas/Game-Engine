#include "ParticleSystem.h"

namespace Systemstate
{
  enum Systemstates
  {
    wander,
    ocean,
    size
  };
};
ParticleSystem::ParticleSystem()
{
  state = -1;
  
  std::string temp =  "Use the Left or Right arrow keys to cycle through.\n";
  effect.SetText(temp);
  effect.SetSize(20.0f);
  effect.SetStyle(sf::String::Bold);
  effect.SetPosition(10, 10);
}
ParticleSystem::~ParticleSystem()
{
}
void ParticleSystem::ChangeState()
{
  for (unsigned i = 0; i < vectorOfManagers.size(); ++i)
  {
    delete vectorOfManagers[i];
  }
  vectorOfManagers.clear();

  ParticleManager<ParticleGroup> * temp = new ParticleManager<ParticleGroup>;
  temp->trans = this->trans;

  state = state % (Systemstate::size);
  if ( state == Systemstate::wander )
  {
    effect.SetText("Wandering Particles.");
    for (unsigned i = 0; i < 100; ++i)
    {
      temp->AddParticle(new ParticleGroup(30));
    }
    temp->mode = GlMode::glLines | GlMode::glPoints;
    vectorOfManagers.push_back(temp);
  }
  else if (state == Systemstate::ocean)
  {
    effect.SetText("Ocean.");
    for (int j = 0; j < 32000; ++j)
      temp->AddParticle(new ParticleGroup(0, 1.0f, .8f, 1.0f, 1.0f));
    temp->mode =GlMode::glPoints;
    vectorOfManagers.push_back(temp);

    //Add a wander within it
    temp = new ParticleManager<ParticleGroup>;
    temp->trans = this->trans;
    temp->AddParticle(new Water(20));
    temp->mode = GlMode::glDraw;
    
    vectorOfManagers.push_back(temp);

  }
  
}
void ParticleSystem::BroadcastMessage(Message * message)
{
  //Recieve inputs for the ParticleSystem
  //Intialise the relevant particleManagers for each differing input
  int key = (int)(message->info);
  if (message->msgID == MessageID::CharacterKey)
  {
    if (key == sf::Key::Right)
    {
      //Go to next manager state with its own intialises
      ++state;
      //Call the function that intialises depending on what state.
      ChangeState();
    }
    else if (key == sf::Key::Left)
    {
      --state;//Go to previous state
      //Call the function that intialises depending on what state.
      ChangeState();
    }
  }
}

void ParticleSystem::DrawGL()
{
  for (unsigned i = 0; i < vectorOfManagers.size(); ++i)
  {
    vectorOfManagers[i]->DrawGL();
  }
  g_App->Draw(effect);
}

