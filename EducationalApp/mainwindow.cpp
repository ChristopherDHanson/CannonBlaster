#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <SFML/Audio.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spriteTimer.setInterval(40);
    connect(&spriteTimer, &QTimer::timeout, this, &MainWindow::updateSprite);

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
//    sf::Music music;
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }

    // Play the music
    music.play();

    ui->widget->addSprite(sprite);
    spriteTimer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sprite;
}

void MainWindow::updateSprite()
{
    sprite->rotate(1.0);
    sprite->setTexture(textures[(spriteSwapIdx++ / 20) % 2]);
}
