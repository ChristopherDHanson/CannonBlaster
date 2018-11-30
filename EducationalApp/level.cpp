#include "level.h"
#include <Box2D/Box2D.h>

Level::Level(float32 gravity, float32 timeStep)
{
    this->timeStep = timeStep;
    b2Vec2 gravityF = b2Vec2(0.0f, gravity);
    world = new b2World(gravityF);
}

void Level::createBox(float32 width, float height, float32 posX, float32 posY)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX, posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape firstBox;
    firstBox.SetAsBox(width/2, height/2);
    body->CreateFixture(&firstBox, 0.0f);
    bodies.push_back(body);
}

void Level::next()
{
    world->Step(timeStep, 6, 2);
}
