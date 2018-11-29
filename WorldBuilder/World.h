#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include "Shape.h"

class World{
  b2World world;
  float32 timeStep;
public:
  World(float32 gravity, float32 timeStep);
  Shape CreateBox(float32 width, float height, float32 posX, float32 posY);
  void Next();
};



#endif
