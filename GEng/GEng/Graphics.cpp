#include "Graphics.h"
#include "Globals.h"
#include <iostream>
#include <SFML\Window.hpp>
#include <vector>
#include "ParticleSystem.h"
#include "Graphics.h"
#include "RoughSketch.h"
#define WHITE 1.0, 1.0, 1.0
#define RED 1.0, 0.0, 0.0
#define GREEN 0.0, 1.0, 0.0
#define BLUE 0.0, 0.0, 0.0
#define BLACK 0.0, 0.0, 0.0

std::map<unsigned int,GraphicsComponent*> NonTexInstances;
std::map<unsigned int,GraphicsComponent*> TexInstances;

void Graphics::BroadcastMessage(Message * message)
{
  if(message->msgID == MessageID::CharacterKey)
  {
    std::cout << "Character Key was pressed." << std::endl;
    if ((int)message->info == sf::Key::F1)
    {
      fullscreen = !fullscreen;
      g_App->Create(fullscreen ? sf::VideoMode::GetDesktopMode() : sf::VideoMode(800, 600, 32) , "ParticleTest",
                        (fullscreen ? sf::Style::Fullscreen : sf::Style::Resize | sf::Style::Close));
      ResizeScreen(g_App->GetWidth(), g_App->GetHeight());
      
    }
  }
  else if(message->msgID == MessageID::Spawn)
    CallSpawnFunction(dynamic_cast<SpawnMessage *>(message));

};

void Graphics::ResizeScreen(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  glOrtho(0, (float)width, (float)height, 0, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_LINE_SMOOTH);
  glDisable(GL_POINT_SMOOTH);
  glPointSize(3*(float)width/800.0f);
  glLineWidth(3*(float)width/800.0f);
 
  glScalef((float)width/800.0f,  (600.0f/800.0f)*(float)width, 1.0f);
}

 float rndcolors[10][10];
 
void Graphics::Update(float timeslice)
{
  /*GL_BLEND / GL_TEXTURE_2D
    Those settings will be disabled / enabled
    by the entities that need to call them.
    although constant disabling enabling is unwanted.
    it would be better to draw the textured stuff together*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glScalef((float)g_App->GetWidth() / 800.0f, g_App->GetWidth()/800.0f, 1.0f);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor4f(WHITE, 1.0);
 

 
 // glEnable(GL_SCISSOR_TEST);
  //glScissor(0, 500, 500, 100);
 /*    for (int i =0; i < TexInstances.size() ; ++i)
  {
   // glBindTexture(GL_TEXTURE_2D, Models[EntityID::Icecream].texture);
    TexInstances[i]->DrawGL();
  }*/
  glDisable(GL_TEXTURE_2D);
  for (std::map<unsigned, GraphicsComponent*>::iterator itr = NonTexInstances.begin() ; itr != NonTexInstances.end(); ++itr)
  {

    itr->second->DrawGL();
  }


  
  
 // glEnable(GL_BLEND);
 /* glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  float * pArr;
  float color[] = {1.0, 0.0,0.0,0.0, 0.0,1.0,0.0, 0.0, 0.0, 0.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  float coord[] = {200.0, 300.0, 400.0, 300.0, 250.0, 200.0};
  pArr = &coord[0];
  glColorPointer(4, GL_FLOAT, 0, color);
  glVertexPointer(2, GL_FLOAT, 0, pArr);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  float dude[] ={300.0, 400.0, 100.0, 600.0, 300.0, 100.0};
  glColorPointer(4, GL_FLOAT, 0, color);
  glVertexPointer(2, GL_FLOAT, 0, dude);
  glDrawArrays(GL_TRIANGLES, 0, 3);*/

 
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glTranslatef(0.0f, 0.0f, -30.0f);
 
	
  //Component::scrnHeight = 600; Component::scrnWidth = 800;
	App.Display();
};

std::string Graphics::GetName() 
{
  return 0;
};

void Graphics::Initialize()
{
  App.Create(sf::VideoMode(800, 600 ,32), "ParticleTest");
  glViewport(0, 0, 800, 600);
  glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
 // glDisable(GL_DEPTH_TEST);
  glDepthFunc(GL_NEVER);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glShadeModel(GL_SMOOTH);
  glLoadIdentity();
  glOrtho(0, 800, 600,0, -100, 100);
  glDisable(GL_POINT_SMOOTH);
  //gluPerspective(45.0f, (GLfloat)800/(GLfloat)600, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  g_App = &App;
  glPointSize(3.0);
  glLineWidth(3.0);
  //Order of pushback Important
  Models.resize(EntityID::LastID);
  OurImage localIcecream;
  localIcecream.sfImage.LoadFromFile("ice-cream-chargers.jpg");
  localIcecream.eType = EntityID::Icecream;
  //glGenTextures(1, &(icecream->texture));
  glGenTextures(1, &(localIcecream.texture));
  glBindTexture(GL_TEXTURE_2D, localIcecream.texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, localIcecream.sfImage.GetWidth(), localIcecream.sfImage.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, localIcecream.sfImage.GetPixelsPtr());

  Models[EntityID::Icecream] =localIcecream;
  
  fullscreen = false;
  //glBindTexture(GL_TEXTURE_2D, Models[EntityID::Icecream]->texture);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //NonTexInstances[100] = new RoughSketch;
 
  for (int i = 0; i < 100; ++i)
  {
    rndcolors[i/10][i%10] = sf::Randomizer::Random(0.0f, 1.0f);
  }
};

Graphics::~Graphics()
{
};


void Graphics::CallSpawnFunction(SpawnMessage* spawn)
{
  //relevant ifs to determine spawn type
  if (spawn->type == EntityID::Icecream)
  {
    GraphicsComponent *gcp = new GraphicsComponent;
    gcp->SetComponentId(CompID::Graphics);
    //gcp->type = EntityID::Icecream;
    gcp->trans = spawn->trans;
    gcp->SetOwner(spawn->owner);
    //pushes GCP, into the entity components 
    //that was passed in through the message.
    spawn->components->push_back(gcp);

    TexInstances[spawn->entid] = gcp;
  
  }
  else if (spawn->type == EntityID::ParticleGroup)
  {
   /*ParticleGroup *gcp;
    if (spawn->info == NULL)
      gcp = new ParticleGroup(1.0f,0.f,0.f, 30);
    else
    {
      std::cout << (((float *)spawn->info)[4]);
      gcp = new ParticleGroup((((float *)spawn->info)[1]), (((float *)spawn->info)[2]), (((float *)spawn->info)[3]), 
        (((float *)spawn->info)[4]), (((float *)spawn->info)[5]));
      //gcp = new ParticleGroup;
    }
    gcp->SetComponentId(CompID::ParticleGroup);
    //gcp->type = EntityID::ParticleGroup;
    gcp->trans = spawn->trans;
    gcp->SetOwner(spawn->owner);
    spawn->components->push_back(gcp);*/

 
    //NonTexInstances.push_back(gcp);
  }
  else if (spawn->type == EntityID::ParticleManager)
  {
    ParticleManager<ParticleGroup> *pcp = new ParticleManager<ParticleGroup>;
    pcp->trans = spawn->trans;
    pcp->SetOwner(spawn->owner);
    spawn->components->push_back(pcp);
    for (int i = 0; i < 50; ++i)
      pcp->AddParticle(new ParticleGroup(100));
    NonTexInstances[spawn->entid] = pcp;
  }
  else if (spawn->type == EntityID::ParticleSystem)
  {
    ParticleSystem * psys = new ParticleSystem;
    psys->trans = spawn->trans;
    psys->SetOwner(spawn->owner);
    spawn->components->push_back(psys);
    NonTexInstances[spawn->entid] = psys;
  }
};



 