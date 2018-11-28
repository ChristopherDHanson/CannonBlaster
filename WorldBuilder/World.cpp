#include "World.h"
#include <Box2D/Box2D.h>

World::World(float32 gravity, float32 timeStep):
  timeStep(timeStep)
{
  b2Vec2 gravityF(0.0f, gravity);
  b2World newWorld(gravityF);
  this.world = newWorld;
}

Shape World::CreateBox(float32 width, float height, float32 posX, float32 posY)
{
  b2PolygonShape firstBox;
  firstBox.SetAsBox(width/2, height/2);
  firstBody->CreateFixture(&firstBox, 0.0f);
}

void World::Next()
{
  // TODO
}
