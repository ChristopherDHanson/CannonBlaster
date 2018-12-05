#include <iostream>
#include <vector>
#include <cmath>

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
    connect(ui->angleSlider, &QSlider::sliderMoved, this, &DemoWindow::changeAngle);
    connect(ui->velocitySlider, &QSlider::sliderMoved, this, &DemoWindow::changeVelocity);
    connect(ui->massSlider, &QSlider::sliderMoved, this, &DemoWindow::changeDensity);

    spriteTimer.setInterval(40);
    connect(&spriteTimer, &QTimer::timeout, this, &DemoWindow::updateSprites);

    velocity = 1;
    angle[0] = 0;
    angle[1] = 1;
    density = 1;

    // CONSTRUCT LEVELS--------
    // General process is: 1) Construct level, 2) Load its textures, 3) Add elements
    // Level 1:
    Level* level1 = new Level(-2.0f, 0.04f, 64.0f);

<<<<<<< HEAD
    textures = std::vector<sf::Texture>(4);
    if (!textures[0].loadFromFile("../Images/coinSprite1.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[1].loadFromFile("../Images/coinSprite2.png")) {
=======
    textures = std::vector<sf::Texture>(2);
    if (!textures[0].loadFromFile("../images/bullet.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[1].loadFromFile("../images/box.png")) {
>>>>>>> eec4e9f6f8d7903d433615185a134991ac224c6e
        throw "EXIT_FAILURE";
    }

    if (!textures[2].loadFromFile("../Images/coinSprite3.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[3].loadFromFile("../Images/coinSprite4.png")) {
        throw "EXIT_FAILURE";
    }

    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
    textures[2].setSmooth(true);
    textures[3].setSmooth(true);
    level1->loadTextures(textures);

    sf::Vector2u imgSize = textures[1].copyToImage().getSize();
    level1->createBox(imgSize.x,imgSize.y,300,100);
    level1->createInvisibleBox(500,10,100,320);
    level1->setLevelSpeed(6);
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

    // Music stuff
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }
    // Play the music
    music.play();

    // Add current level sprites to the canvas
    currentLevel = levels[0];
    for (sf::Sprite* s : currentLevel->sprites)
    {
     ui->canvas->addSprite(s);
    }

    loadBackground();
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
    // Set position of each sprite to position of corresponding physics body
    for (int index = 0; index < currentLevel->sprites.size(); index++) {
        sf::Sprite* s = currentLevel->sprites[index];
        b2Vec2 pos = currentLevel->bodies[index]->GetPosition();
<<<<<<< HEAD
        s->setPosition(pos.x, pos.y);
//        s->setPosition(pos.x*currentLevel->pixelsPerUnit, pos.y*currentLevel->pixelsPerUnit);
        //s->rotate(1.0);
        s->setTexture(textures[(spriteSwapIdx / 10) % 4]);
=======
        s->setPosition(pos.x, -1 * pos.y );//+ ui->canvas->height());
        //s->rotate(1.0);
        //s->setTexture(textures[(spriteSwapIdx++ / 20) % 2]);
        //std::cout << pos.x << " " <<pos.y << "  \n";
>>>>>>> eec4e9f6f8d7903d433615185a134991ac224c6e
    }
    spriteSwapIdx++;
}

void DemoWindow::spawnCannonball()
{
<<<<<<< HEAD
    sprite = new sf::Sprite(textures[0]);
    currentLevel->createDynamicObject(8,8,300,100,b2Vec2(100,100));
=======
    sf::Vector2u imgSize = textures[0].copyToImage().getSize();
    currentLevel->createDynamicObject(imgSize.x,imgSize.y,0,250,b2Vec2(angle[0] * velocity, angle[1] * velocity), density);
>>>>>>> eec4e9f6f8d7903d433615185a134991ac224c6e
    ui->canvas->addSprite(currentLevel->sprites[currentLevel->sprites.size()-1]);
}

void DemoWindow::loadBackground()
{
    ui->canvas->setBackdrop("../images/golden_forest.jpg");
}

void DemoWindow::changeAngle()
{
    angle[0] = cos(ui->angleSlider->value() * 3.141 / 180);
    angle[1] = sin(ui->angleSlider->value() * 3.141 / 180);
}

void DemoWindow::changeVelocity()
{
    velocity = ui->velocitySlider->value() / 10.0;
    std::cout << velocity << std::endl;
}

void DemoWindow::changeDensity()
{
    density = ui->massSlider->value();
}
