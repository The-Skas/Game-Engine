#include "Water.h"
#include "ParticleWander.h"
#include "Graphics.h"
float scalePerlin;

float speed;
Water::Water(int setsize)
{
 /* Entity * ent = new Entity;
  ENTLIST->AddEntity(ent);

  //GraphicsComponent * gcp = (new Water(15));
  ent->AddComponent(this);

 // NonTexInstances[ent->ID] = this;*/
  masked = 0;
  speed = 0;
  size = setsize;
  angle = 0;
  coordincr = 900/(float)size;
  angleYincr = 1.0f*(360.0f/(float)size)*3.14159265359f/180.0f;
  velocityX = 0;
  velocityY = 0;
  scalePerlin = 3.0f;
  perlin = new PerlinNoise(size, scalePerlin);

  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j< size; ++j)
    {
      for (int k = 0; k < 4; ++k)
      {
        
        color[i][j][k].a = sf::Randomizer::Random(0.95f, 1.0f);
       
        if (j == 0)
        {
          if (k == 0 || k==3)
          {
            color[i][j][k].a = 0;
          }
        }
        else if (j==(size-1))
        {
          if (k==2 || k == 1)
          {
            color[i][j][k].a = 0;
          }
        }

        color[i][j][k].b = sf::Randomizer::Random(0.4f, 0.5f);
        color[i][j][k].g = sf::Randomizer::Random(0.3f, 0.4f);
        color[i][j][k].r = sf::Randomizer::Random(0.0f, 0.1f);
      }
    }
  }
}
void glColor4fWrap(color4 &temp)
{
  float scale = 1.0f;
  glColor4f(temp.r, temp.g, temp.b, temp.a);

 // temp.r += sf::Randomizer::Random(-0.05f, 0.05f);
  if (temp.g >= 0.3f)
    temp.g += sf::Randomizer::Random(0.0f, -0.050f)*scale;
  else
   temp.g +=sf::Randomizer::Random(-0.05f, 0.05f)*scale;

  if (temp.r >= 0.05f)
    temp.r += sf::Randomizer::Random(0.0f, -0.02f)*scale;
  else
    temp.r += sf::Randomizer::Random(-0.02f, 0.02f)*scale;

}

void Water::DrawGL()
{
  glLoadIdentity();
  if (masked)
    glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
  else
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
    DrawQuadsGL();
  glEnd();
 // glColorMask(0, 0, 0, 1);
 // glBlendFunc(GL_, GL_ZERO);
  float scalex, scaley;
  scalex = scaley = 4;
  glScalef(scalex,scaley,1);
  glPointSize(scalex*1);
 // glPointSize(1);
 // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  
  glBegin(GL_POINTS);
    DrawPointsGL();
  glEnd();
  glScalef(1/scalex,1/scaley,1);
 // glBlendFunc(GL_DST_ALPHA, GL_ZERO);

}
void Water::DrawPointsGL()
{
  float scalet = 15.0f;
  float scale = perlin->length/scalet;
  for (float j = 0; j < perlin->length-1; )
  {
    for (float i = 0; i<perlin->width-1; )
    {
      float rndm = perlin->Perlin2D((float)i,j);
      glColor4f(rndm+0.15f, rndm+0.15f,rndm+0.15f, 0.2f);
      glVertex2f((i*scalet/scale), j*scalet/scale+speed);
      i+= scale/scalet;
    }
     j+= scale/scalet;
  }
//speed +=0.5;
};

void Water::DrawQuadsGL()
{
  glColor4f(0.2f, 0.5f, 1.0f, 0.8f);
  glVertex2f(0, 0);
  glVertex2f(0, 600);
  glVertex2f(800, 600);
  glVertex2f(800, 0);
 /* for (float y = 0; y < size; y++)
  {
    for (float x = 0; x < size; x++)
    {
      float sinwave = sin(angle+(y*angleYincr))*5.0f-50.0f;
      glColor4fWrap(color[(int)x][(int)y][0]);
      glVertex2f(coordincr*x+sinwave, coordincr*y );
      glColor4fWrap(color[(int)x][(int)y][1]);
      glVertex2f(coordincr*(x-1)+sinwave, coordincr*y);
      glColor4fWrap(color[(int)x][(int)y][2]);
      glVertex2f(coordincr*(x-1)+sinwave, coordincr*(y-1.0));
      glColor4fWrap(color[(int)x][(int)y][3]);
      glVertex2f(coordincr*x+sinwave, coordincr*(y-1.0));
 
    }
    //break;
  }*/
  angle += 0.015f;
}

void Water::DrawLinesGL()
{
}

Water::~Water()
{
  delete perlin;
}