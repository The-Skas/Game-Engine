#ifndef TRANSFORM
#define TRANSFORM

#include <SFML\System\Vector2.hpp>

class Transform
{
public:
  /*void SetPos(sf::Vector2i vec);
  void SetRot(float rot);

  sf::Vector2i GetPos(void);
  float        GetRot(void);*/


  sf::Vector2f position;
  float rotation;
};

#endif