#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>
#include <Box2D/Box2D.h>
#include "shape.h"

class Level
{
    b2World *world;
    float32 timeStep;
public:
    Level(float32 gravity = -10.0f, float32 timeStep = 1.0f/60.0f);
    void createBox(float32 width = 10, float height = 10, float32 posX = 0, float32 posY = 0);
    void next();
    QVector<b2Body*> bodies;
};

#endif // LEVEL_H
