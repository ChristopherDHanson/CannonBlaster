#include "world.h"
#include <Box2D/Box2D.h>

World::World(float32 gravity, float32 timeStep)
{
    this->timeStep = timeStep;
    gravityF = b2Vec2(0.0f, gravity);
    //b2World newWorld(gravityF);
    //world = newWorld;
    world(gravityF);
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
