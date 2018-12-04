#include "level.h"
#include <Box2D/Box2D.h>

Level::Level(float32 gravity, float32 timeStep, float32 pixelsPerUnit)
{
    this->timeStep = timeStep;
    this->pixelsPerUnit = pixelsPerUnit;
    b2Vec2 gravityF = b2Vec2(0.0f, gravity);
    world = new b2World(gravityF);
}

void Level::loadTextures(std::vector<sf::Texture> inputTextures) {
    textures = inputTextures;
}

void Level::createBox(float32 width, float32 height, float32 posX, float32 posY)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }
    // Set up physical box
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX/pixelsPerUnit, posY/pixelsPerUnit);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width/2/pixelsPerUnit, height/2/pixelsPerUnit);
    body->CreateFixture(&box, 1.0f);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[0]);

    sprite->setOrigin(posX,posY);
    sprite->setPosition(0,0);
    sprites.push_back(sprite);
}

void Level::createDynamicObject(float32 width, float32 height, float32 posX, float32 posY, b2Vec2 force)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }
    // Set up physical box
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posX/pixelsPerUnit, posY/pixelsPerUnit);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width, height);
    body->CreateFixture(&box, 1.0f);
    //body->ApplyLinearImpulseToCenter(b2Vec2(horizForce, 0), true);
<<<<<<< HEAD
    body->SetLinearVelocity(force);
=======
    body->SetLinearVelocity(b2Vec2(horizForce/pixelsPerUnit, 0));
>>>>>>> 835aab10dd73f9f0fceb25468716eb43054958c2
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[0]);

    sprite->setOrigin(posX/pixelsPerUnit,posY/pixelsPerUnit);
    sprite->setPosition(posX/pixelsPerUnit,posY/pixelsPerUnit);
    sprites.push_back(sprite);
}

void Level::next()
{
    world->Step(timeStep, 6, 2);
}
