#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include "shape.h"

class World
{
    b2World world;
    b2Vec2 gravityF;
    float32 timeStep;
public:
    World(float32 gravity, float32 timeStep);
    Shape createBox(float32 width, float height, float32 posX, float32 posY);
    void next();
};

#endif // WORLD_H
