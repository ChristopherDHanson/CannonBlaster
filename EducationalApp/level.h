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
    int levelSpeed = 3;
    QVector<b2Vec2> answerBoxPositions = {b2Vec2(0, 0),b2Vec2(0, 0),b2Vec2(0, 0),b2Vec2(0, 0)};
    std::string musicPath;
    int test;
    std::string background;
    sf::Sprite* cannon;

public:
    Level(float32 gravity = -3.0f, float32 timeStep = 1.0f/60.0f, float32 pixelsPerUnit = 64.0f);
    void loadTextures(std::vector<sf::Texture> inputTextures);
    void createBox(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0, int textureNumber = 0);
    void createCircle(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0);
    void createCircleNew(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0, int textureNumber = 0);
    void createDynamicBox(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0, b2Vec2 force = b2Vec2(0,0), float32 density = 1,int textureNumber = 0);
    void createDynamicCircle(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0, b2Vec2 force = b2Vec2(0,0), float32 density = 1);
    void createInvisibleBox(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0);
    void fireCannonball(b2Vec2 force = b2Vec2(0,0), float32 density = 1.0f);
    void setLevelSpeed(int speed);
    void createCannon(float32 width = 1, float32 height = 1, float32 posX = 0, float32 posY = 0, int textureNumber = 0);
    void setCannonLocation(b2Vec2 cannonLoc);
    void next();
    QVector<b2Vec2> getAnswerBoxPositions();
    void setAnswerBoxPositions(QVector<b2Vec2> pos);
//    void setAnswerBoxPositions(int posXBoxA, int posYBoxA, int posXBoxB, int posYBoxB, int posXBoxC, int posYBoxC, int posXBoxD, int posYBoxD);
    void setBackground(std::string bg);
    std::string getBackground();
    void setCannon(sf::Sprite* cannon);
    sf::Sprite* getCannon();
    void setMusicPath(std::string musicPath);
    std::string getMusicPath();
    sf::Texture* getTexturePtr(uint ind);

    QVector<b2Body*> bodies; // Physics information for each object stored here
    QVector<sf::Sprite*> sprites; // Sprites representing each object stored here
    float32 pixelsPerUnit;
    b2Vec2 cannonLocation = b2Vec2(0,-100);


};

#endif // LEVEL_H
