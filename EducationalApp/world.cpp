#include "world.h"
#include <Box2D/Box2D.h>

World::World(float32 gravity, float32 timeStep)
{
    this->timeStep = timeStep;
    b2Vec2 gravityF(0.0f, gravity);
    world = new b2World(gravityF);
}

Shape World::createBox(float32 width, float height, float32 posX, float32 posY)
{
    b2BodyDef firstBodyDef;
    firstBodyDef.position.Set(posX, posY);
    b2Body* firstBody = world->CreateBody(&firstBodyDef);
    b2PolygonShape firstBox;
    firstBox.SetAsBox(width/2, height/2);
    firstBody->CreateFixture(&firstBox, 0.0f);
}

void World::next()
{
    // TODO
}
