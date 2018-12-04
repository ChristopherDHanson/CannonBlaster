#include <iostream>
#include <vector>

#include "demowindow.h"
#include "ui_demowindow.h"

//#include <SFML/Audio.hpp>

DemoWindow::DemoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DemoWindow)
{
    ui->setupUi(this);

    // CONNECTIONS
    connect(ui->fireButton, &QPushButton::pressed, this, &DemoWindow::spawnCannonball);

    spriteTimer.setInterval(40);
    connect(&spriteTimer, &QTimer::timeout, this, &DemoWindow::updateSprites);


    // CONSTRUCT LEVELS--------
    // General process is: 1) Construct level, 2) Load its textures, 3) Add elements
    // Level 1:
    Level* level1 = new Level(-10.0f, 4.0f / 100.0f);

    textures = std::vector<sf::Texture>(4);
    if (!textures[0].loadFromFile("../Sprites/coinSprite1.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[1].loadFromFile("../Sprites/coinSprite2.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[2].loadFromFile("../Sprites/coinSprite3.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[3].loadFromFile("../Sprites/coinSprite4.png")) {
        throw "EXIT_FAILURE";
    }

    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
    textures[2].setSmooth(true);
    textures[3].setSmooth(true);
    level1->loadTextures(textures);

    //level1->createBox(5.0f, 5.0f, 10.0f, 10.0f);
    levels.push_back(level1);

    // repeat process for further levels
    // ------------------------


    spriteSwapIdx = 0;

    // Initial test sprite
//    // Load a sprite to display
//    textures = std::vector<sf::Texture>(2);
//    if (!textures[0].loadFromFile("../icon.png")) {
//        throw "EXIT_FAILURE";
//    }

//    if (!textures[1].loadFromFile("../icon2.png")) {
//        throw "EXIT_FAILURE";
//    }
//    textures[0].setSmooth(true);
//    textures[1].setSmooth(true);
//    // Create the sprite
//    sprite = new sf::Sprite(textures[0]);

//    sprite->setOrigin(200,100);
//    sprite->setPosition(350,250);
//    sprites.push_back(sprite);
//    ui->canvas->addSprite(sprite);

//    sf::Music music;
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }

    // Play the music
    music.play();

    // GOAL:
    currentLevel = levels[0];
     for (sf::Sprite* s : currentLevel->sprites)
     {
         ui->canvas->addSprite(s);
     }
    spriteTimer.start();
}

DemoWindow::~DemoWindow()
{
    delete ui;
    delete sprite;
}

void DemoWindow::updateSprites()
{
    // Update level physics state
    currentLevel->next();
    // call update on all shapes
    for (int index = 0; index < currentLevel->sprites.size(); index++) {
        sf::Sprite* s = currentLevel->sprites[index];
        b2Vec2 pos = currentLevel->bodies[index]->GetPosition();
        s->setPosition(pos.x, pos.y);
        //s->rotate(1.0);
        s->setTexture(textures[(spriteSwapIdx / 10) % 4]);
    }
    spriteSwapIdx++;
}

void DemoWindow::spawnCannonball()
{
    sprite = new sf::Sprite(textures[0]);
    currentLevel->createDynamicObject(8,8,250,500,b2Vec2(100,100));
    ui->canvas->addSprite(currentLevel->sprites[currentLevel->sprites.size()-1]);
}
