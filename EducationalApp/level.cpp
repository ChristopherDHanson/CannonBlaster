#include "level.h"
#include <Box2D/Box2D.h>

Level::Level(float32 gravity, float32 timeStep)
{
    this->timeStep = timeStep;
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
    bodyDef.position.Set(posX, posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width/2, height/2);
    body->CreateFixture(&box, 1.0f);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[0]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    sprite->setOrigin(temp.x,temp.y);
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
    bodyDef.position.Set(posX, -1 * posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width, height);
    body->CreateFixture(&box, 1.0f);
    //body->ApplyLinearImpulseToCenter(force, true);
    //body->ApplyForceToCenter(force, true);
    body->SetLinearVelocity(force);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[0]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    //sprite->setOrigin(30,30);
    sprite->setPosition(temp.x, -1 * temp.y);
    sprites.push_back(sprite);
}

void Level::next()
{
    world->Step(timeStep, 6, 2);
}
