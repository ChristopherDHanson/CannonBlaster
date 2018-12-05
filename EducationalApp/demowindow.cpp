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

    velocity = 20;
    angle[0] = cos(ui->angleSlider->value() * 3.141 / 180);
    angle[1] = sin(ui->angleSlider->value() * 3.141 / 180);
    density = 1;

    // CONSTRUCT LEVELS--------
    // General process is: 1) Construct level, 2) Load its textures, 3) Add elements
    // Level 1:
    Level* level1 = new Level(-2.0f, 0.04f, 64.0f);

    textures = std::vector<sf::Texture>(9);
    if (!textures[0].loadFromFile("../Images/coinSprite1.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[1].loadFromFile("../Images/coinSprite2.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[2].loadFromFile("../Images/coinSprite3.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[3].loadFromFile("../Images/coinSprite4.png")) {
        throw "EXIT_FAILURE";
    }

    // if (textures[4].loadFromFile("../Images/SpringBlocks/springBlock2Short.png")) {
    //    throw "EXIT_FAILURE";
    //}
    if (!textures[4].loadFromFile("../images/bricks.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[5].loadFromFile("../Images/SpringBlocks/springBlock1.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[6].loadFromFile("../Images/SpringBlocks/springBlock2.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[7].loadFromFile("../Images/SpringBlocks/springBlock2.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[8].loadFromFile("../Images/SpringBlocks/springTree.png")) {
        throw "EXIT_FAILURE";
    }

    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
    textures[2].setSmooth(true);
    textures[3].setSmooth(true);
    textures[4].setSmooth(true);
    textures[5].setSmooth(true);
    textures[6].setSmooth(true);
    textures[7].setSmooth(true);
    textures[8].setSmooth(true);

    level1->loadTextures(textures);

    // sf::Vector2u imgSize = textures[4].copyToImage().getSize();
    // level1->createBox(imgSize.x,imgSize.y,300,100);
    // level1->createInvisibleBox(500,10,100,320);



    sf::Vector2u imgSize = textures[1].copyToImage().getSize();
    level1->createDynamicBox(50,50,500,250, b2Vec2(0,0), 1, 2);
    level1->createDynamicBox(50,50,550,250, b2Vec2(0,0), 1, 2);
    level1->createDynamicBox(50,50,600,250, b2Vec2(0,0), 1, 2);
    level1->createDynamicBox(50,50,525,150, b2Vec2(0,0), 1, 2);
    level1->createDynamicBox(50,50,575,150, b2Vec2(0,0), 1, 2);
    level1->createDynamicBox(50,50,550,50, b2Vec2(0,0), 1, 2);
    level1->createInvisibleBox(5000,10,100,320);
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
    //music.play();  **********************************************************************************************

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
        s->setPosition(pos.x, -1 * pos.y );//+ ui->canvas->height());
        //s->rotate(1.0);
//        s->setTexture(textures[(spriteSwapIdx / 5) % 4]);
        //std::cout << pos.x << " " <<pos.y << "  \n";
    }
    spriteSwapIdx++;
}

void DemoWindow::spawnCannonball()
{
    sf::Vector2u imgSize = textures[0].copyToImage().getSize();
    currentLevel->createDynamicCircle(imgSize.x,imgSize.y,0,250,b2Vec2(angle[0] * velocity, angle[1] * velocity), density);
    ui->canvas->addSprite(currentLevel->sprites[currentLevel->sprites.size()-1]);
}

void DemoWindow::loadBackground()
{
    ui->canvas->setBackdrop("../Images/springBckgrnd.png");
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
