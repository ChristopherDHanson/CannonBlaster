#ifndef LEVEL_H
#define LEVEL_H

#include <stdexcept>
#include <QVector>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "shape.h"

class Level
{
private:
    b2World *world;
    float32 timeStep;
    std::vector<sf::Texture> textures; // Raw textures stored here
public:
    Level(float32 gravity = -10.0f, float32 timeStep = 1.0f/60.0f);
    void loadTextures(std::vector<sf::Texture> inputTextures);
    void createBox(float32 width = 10, float height = 10, float32 posX = 0, float32 posY = 0);
    void next();
    QVector<b2Body*> bodies; // Physics information for each object stored here
    QVector<sf::Sprite*> sprites; // Sprites representing each object stored here

};

#endif // LEVEL_H
