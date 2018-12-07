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

void Level::createInvisibleBox(float32 width, float32 height, float32 posX, float32 posY)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }
    // Set up physical box
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posX, -1 * posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width/2.0f, height/2.0f);
    body->CreateFixture(&box, 1.0f);

}

void Level::createBox(float32 width, float32 height, float32 posX, float32 posY, int textureNumber)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }
    // Set up physical box
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posX, -1 * posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width/2.0f, height/2.0f);
    body->CreateFixture(&box, 1.0f);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[textureNumber]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    sprite->setOrigin(width/2.0f,height/2.0f);
    sprite->setPosition(temp.x, -1 * temp.y);
    sprites.push_back(sprite);
}

void Level::createCannon (float32 width, float32 height, float32 posX, float32 posY, int textureNumber)
{

}

// for cannonball
void Level::createCircle (float32 width, float32 height, float32 posX, float32 posY)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }
    // Set up physical box
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posX, -1 * posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2CircleShape circle;
    circle.m_radius = width/2.0f;
    body->CreateFixture(&circle, 1.0f);
    bodies.push_back(body);

    // Set up visual box. hardcoded to load cannonball image
    sf::Sprite* sprite = new sf::Sprite(textures[1]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    sprite->setOrigin(width/2.0f,height/2.0f);
    sprite->setPosition(temp.x, -1 * temp.y);
    sprites.push_back(sprite);
}

// for other circle shaped objects
void Level::createCircleNew (float32 width, float32 height, float32 posX, float32 posY, int textureNumber)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }
    // Set up physical box
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posX, -1 * posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2CircleShape circle;
    circle.m_radius = height/2.0f;
    body->CreateFixture(&circle, 1.0f);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[textureNumber]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    sprite->setOrigin(width/2.0f,height/2.0f);
    sprite->setPosition(temp.x, -1 * temp.y);
    sprites.push_back(sprite);
}

void Level::createDynamicBox(float32 width, float32 height, float32 posX, float32 posY, b2Vec2 force, float32 density, int textureNumber)
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
    box.SetAsBox(width/2.0f, height/2.0f);
    body->CreateFixture(&box, density);
    //body->ApplyLinearImpulseToCenter(force, true);
    //body->ApplyForceToCenter(force, true);
    body->SetLinearVelocity(force);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[textureNumber]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    sprite->setOrigin(width/2.0f,height/2.0f);
    sprite->setPosition(temp.x, -1 * temp.y);
    sprites.push_back(sprite);
}

void Level::createDynamicCircle(float32 width, float32 height, float32 posX, float32 posY, b2Vec2 force, float32 density)
{
    if (textures.size() == 0) {
        throw std::runtime_error("Textures array empty");
    }

    // Set up physical circle
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posX, -1 * posY);
    b2Body* body = world->CreateBody(&bodyDef);
    b2CircleShape circle;
    circle.m_radius = width/2.0f;
    body->CreateFixture(&circle, density);
    body->SetLinearVelocity(force);
    bodies.push_back(body);

    // Set up visual box
    sf::Sprite* sprite = new sf::Sprite(textures[0]);

    b2Vec2 temp = bodies[bodies.size() - 1]->GetPosition();
    sprite->setOrigin(width/2.0f,height/2.0f);
    sprite->setPosition(temp.x, -1 * temp.y);
    sprites.push_back(sprite);
}

void Level::fireCannonball(b2Vec2 force, float32 density) {
    createDynamicCircle();
    sf::Vector2u imgSize = textures[0].copyToImage().getSize();
    createDynamicCircle(imgSize.x,imgSize.y,cannonLocation.x,cannonLocation.y, force, density);
}

void Level::setLevelSpeed(int speed) {
    levelSpeed = speed;
}

void Level::setCannonLocation(b2Vec2 cannonLoc) {
    cannonLocation = cannonLoc;
}

void Level::next()
{
    for (int ind = 0; ind < levelSpeed; ind++) {
        world->Step(timeStep, 6, 2);
    }
}

QVector<b2Vec2> Level::getAnswerBoxPositions()
{
    return answerBoxPositions;
}

void Level::setAnswerBoxPositions(QVector<b2Vec2> pos)
{
    answerBoxPositions = pos;
}


std::string Level::getBackground()
{
    return background;
}

void Level::setBackground(std::string bg)
{
    background = bg;
}

void Level::setCannon(sf::Sprite *cannon)
{
    this->cannon = cannon;
}

sf::Sprite* Level::getCannon()
{
    return cannon;
}

void Level::setMusic(std::string musicPath)
{
    if (!music.openFromFile(musicPath)) {
        throw "EXIT_FAILURE";
    }
}
