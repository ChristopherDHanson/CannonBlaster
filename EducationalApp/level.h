#ifndef LEVEL_H
#define LEVEL_H

#include <stdexcept>
#include <QVector>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "shape.h"
//#include "QuestionAPI.h"

class Level
{
private:
    b2World *world;
    float32 timeStep;
    std::vector<sf::Texture> textures; // Raw textures stored here
//    std::vector<Question>

public:
    Level(float32 gravity = -10.0f, float32 timeStep = 1.0f/60.0f, float32 pixelsPerUnit = 64.0f);
    void loadTextures(std::vector<sf::Texture> inputTextures);
    void createBox(float32 width = 1, float height = 1, float32 posX = 0, float32 posY = 0);
    void createDynamicObject(float32 width = 1, float height = 1, float32 posX = 0, float32 posY = 0, float horizForce = 0);
    void next();
    QVector<b2Body*> bodies; // Physics information for each object stored here
    QVector<sf::Sprite*> sprites; // Sprites representing each object stored here
    float32 pixelsPerUnit;

};

#endif // LEVEL_H
