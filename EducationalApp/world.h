#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include "shape.h"

class World
{
<<<<<<< HEAD
    b2World world;
    b2Vec2 gravityF;
=======
    b2World *world;
>>>>>>> 05768446477ef7617d46e44e662d412cf09d2007
    float32 timeStep;
public:
    World(float32 gravity, float32 timeStep);
    Shape createBox(float32 width, float height, float32 posX, float32 posY);
    void next();
};

#endif // WORLD_H
