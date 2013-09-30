#include "RoughSketch.h"

RoughSketch::RoughSketch()
{
if(img.sfImage.loadFromFile("Starinv.png"))
  {
    glGenTextures(1, &(img.texture));
    glBindTexture(GL_TEXTURE_2D, img.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.sfImage.getSize().x, img.sfImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.sfImage.getPixelsPtr());
  }
  trans = new Transform;
  trans->position.x = 400;
  trans->position.y = 300;
};
float width = 300.0f;
float height = 300.0f;
void RoughSketch::DrawGL()
{
  // Now set scissor to smaller red sub region
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D, img.texture);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex2f(this->trans->position.x - width/2.0f, this->trans->position.y - height/2.0f);
      glTexCoord2f(0.0f,1.0f); glVertex2f(this->trans->position.x  - width/2.0f, this->trans->position.y + height/2.0f);
      glTexCoord2f(1.0f,1.0f);glVertex2f( this->trans->position.x  + width/2.0f, this->trans->position.y + height/2.0f);
      glTexCoord2f(1.0f, 0.0f);glVertex2f(this->trans->position.x  + width/2.0f, this->trans->position.y - height/2.0f);
  glEnd();
  glTranslatef(0.0f, 50.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f, 100.0f);
    glTexCoord2f(1.0f,1.0f);glVertex2f(100.0f, 100.0f);
    glTexCoord2f(1.0f, 0.0f);glVertex2f(100.0f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  //Use this to manipulate buffers
  //glColorMask(1, 1, 1, 1);
   // glClear(GL_COLOR_BUFFER_BIT);
  


    // Turn scissor back off for next render
};
void RoughSketch::BroadcastMessage(Message * msg)
{
  if (msg->msgID == MessageID::MouseMove)
  {
    this->trans->position.x =(float) ((sf::Event::MouseMoveEvent *)msg->info)->x;
    this->trans->position.y =(float)((sf::Event::MouseMoveEvent *)msg->info)->y;
  }
}