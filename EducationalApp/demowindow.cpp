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

    nonInteractiveTextures = std::vector<sf::Texture>(5);
    textures = std::vector<sf::Texture>(16);

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

    if (!textures[4].loadFromFile("../Images/blueBlock.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[5].loadFromFile("../Images/SpringBlocks/springGroundWide.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[6].loadFromFile("../Images/SpringBlocks/springBlock2.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[7].loadFromFile("../Images/SpringBlocks/springBlock2Short.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[8].loadFromFile("../Images/SpringBlocks/springTree.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[9].loadFromFile("../Images/SpringBlocks/springTreeTop.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[10].loadFromFile("../Images/SpringBlocks/springTreeMiddle.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[11].loadFromFile("../Images/SpringBlocks/springTreeTrunk.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[12].loadFromFile("../Images/SpringBlocks/springTreeBottom.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[13].loadFromFile("../Images/SpringBlocks/springBlock2Top.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[14].loadFromFile("../Images/SpringBlocks/springBlock2Part.png")) {
        throw "EXIT_FAILURE";
    }

    if (!textures[15].loadFromFile("../Images/SpringBlocks/springBlock2Btm.png")) {
        throw "EXIT_FAILURE";
    }

    if (!nonInteractiveTextures[0].loadFromFile("../Images/cannon1.png")){
        throw "EXIT_FAILURE";
    }

    nonInteractiveTextures[0].setSmooth((true));
    textures[0].setSmooth(true);
    textures[1].setSmooth(true);
    textures[2].setSmooth(true);
    textures[3].setSmooth(true);
    textures[4].setSmooth(true);
    textures[5].setSmooth(true);
    textures[6].setSmooth(true);
    textures[7].setSmooth(true);
    textures[8].setSmooth(true);
    textures[9].setSmooth(true);
    textures[10].setSmooth(true);
    textures[11].setSmooth(true);
    textures[12].setSmooth(true);
    textures[13].setSmooth(true);
    textures[14].setSmooth(true);
    textures[15].setSmooth(true);

    level1->loadTextures(textures);

    // sf::Vector2u imgSize = textures[4].copyToImage().getSize();
    // level1->createBox(imgSize.x,imgSize.y,300,100);
    // level1->createInvisibleBox(500,10,100,320);



//    sf::Vector2u imgSize = textures[1].copyToImage().getSize();

//    level1->createInvisibleBox(5000,10,100,320);

    // PROBABLY CREATE FUNCTIONS FOR COMMON OBJECTS LIKE I DID WITH THE TREES
    // pyramid of blue blocks
    // bottom level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,497,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,513,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,529,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,561,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,577,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,593,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,609,250, b2Vec2(0,0), 1, 4);
    // 2nd level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,497,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,513,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,529,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,561,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,577,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,593,200, b2Vec2(0,0), 1, 4);
    // 3rd level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,513,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,529,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,561,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,577,150, b2Vec2(0,0), 1, 4);
    // 4th level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,529,100, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,100, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,561,100, b2Vec2(0,0), 1, 4);
    // top of pyramid
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,50, b2Vec2(0,0), 1, 4);


    // ground
    level1->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);

    // build a tree from its parts. 2nd parameter is the x position to build
    spawnTree(level1, 250);

    // build a tall tree from its parts. 2nd parameter is the x position to build
    // can create function for taller tree if needed
    spawnTallTree(level1, 180);
    spawnTallTree(level1, 380);

    // build block/wall structure
    level1->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, 650, 200, 13);
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, 650, 222, 14);
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, 650, 254, 14);
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, 650, 286, 14);
    level1->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, 650, 303, 15);


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

    //creating with the cannon without box2d
    cannon = new sf::Sprite(nonInteractiveTextures[0]);
    cannon->setOrigin(nonInteractiveTextures[0].copyToImage().getSize().x/2, nonInteractiveTextures[0].copyToImage().getSize().y/2);
    cannon->setPosition(50, 250);

    //adding it to the canvas sprites
    ui->canvas->addSprite(cannon);

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

void DemoWindow::spawnTree(Level* level1, float32 posX)
{
    level1->createBox(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 267, 9);    //leaves
    level1->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 284, 10); //middle
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 291, 11); //trunk
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 298, 11); //trunk
    level1->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::spawnTallTree(Level* level1, float32 posX)
{
    level1->createBox(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 253, 9);    //leaves
    level1->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 270, 10); //middle
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 277, 11); //trunk
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 284, 11); //trunk
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 291, 11); //trunk
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 298, 11); //trunk
    level1->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
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
    if(ui->angleSlider->value() < angle[2])
    {
        cannon->rotate(1);
        cannon->rotate(0);
    }
    else
    {
        cannon->rotate(-1);
        cannon->rotate(0);
    }
    angle[0] = cos(ui->angleSlider->value() * 3.141 / 180);
    angle[1] = sin(ui->angleSlider->value() * 3.141 / 180);
    angle[2] = ui->angleSlider->value();

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
