#ifndef GENG_SRC_ROUGHSKETCH_H_
#define GENG_SRC_ROUGHSKETCH_H_
#include "GraphicsComponent.h"
#include "Graphics.h"
class RoughSketch : public GraphicsComponent
{
public:
  RoughSketch();
  void DrawGL();
  void BroadcastMessage(Message * msg);
private:
  OurImage img;
};
#endif