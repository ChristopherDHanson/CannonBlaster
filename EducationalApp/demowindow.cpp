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

    connect(ui->fireButton, &QPushButton::pressed, this, &DemoWindow::spawnCannonball);

    spriteTimer.setInterval(40);
    connect(&spriteTimer, &QTimer::timeout, this, &DemoWindow::updateSprites);

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
    spriteTimer.start();
}

DemoWindow::~DemoWindow()
{
    delete ui;
    delete sprite;
}

void DemoWindow::updateSprites()
{
//    sprite->rotate(1.0);
//    sprite->setTexture(textures[(spriteSwapIdx++ / 20) % 2]);
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
