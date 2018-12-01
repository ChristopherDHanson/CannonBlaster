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

    textures = std::vector<sf::Texture>(2);
    if (!textures[0].loadFromFile("../icon.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[1].loadFromFile("../icon2.png")) {
        throw "EXIT_FAILURE";
    }
    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
    level1->loadTextures(textures);

    level1->createBox(40, 20, 10, 10);
    levels.push_back(level1);

    // repeat process for further levels
    // ------------------------


    spriteSwapIdx = 0;

    // Load a sprite to display
    textures = std::vector<sf::Texture>(2);
    if (!textures[0].loadFromFile("../icon.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[1].loadFromFile("../icon2.png")) {
        throw "EXIT_FAILURE";
    }
    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
    // Create the sprite
    sprite = new sf::Sprite(textures[0]);

    sprite->setOrigin(200,100);
    sprite->setPosition(350,250);
    sprites.push_back(sprite);
//    sf::Music music;
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }

    // Play the music
    music.play();

    ui->canvas->addSprite(sprite);
    // GOAL:
    // for (sf::Sprite* s : currentLevel->sprites) {
    // ui->->canvas->addSprite(s); }
    spriteTimer.start();
}

DemoWindow::~DemoWindow()
{
    delete ui;
    delete sprite;
}

void DemoWindow::updateSprites()
{
    // call update on all shapes
    for (sf::Sprite* s : sprites) {
        s->rotate(1.0);
        s->setTexture(textures[(spriteSwapIdx++ / 20) % 2]);
    }
}

void DemoWindow::spawnCannonball()
{
    sprite = new sf::Sprite(textures[0]);
    sprites.push_back(sprite);
    ui->canvas->addSprite(sprite);
}
