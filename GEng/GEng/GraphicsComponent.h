#ifndef GENG_SRC_GRAPHICSCOMPONENT_H_
#define GENG_SRC_GRAPHICSCOMPONENT_H_
#include "Component.h"
#include "Transform.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
//What an INSTANCE of a model needs, saved in entity list

class SpawnMessage;
class GraphicsComponent : public Component
{
public:
  ~GraphicsComponent(){};
  bool masked;
  Transform *trans;
  virtual void DrawGL(){};
};
#endif 