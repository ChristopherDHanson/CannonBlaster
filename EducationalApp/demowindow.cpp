#include <iostream>
#include <vector>
#include <cmath>

#include "demowindow.h"
#include "ui_demowindow.h"

//#include <SFML/Audio.hpp>

DemoWindow::DemoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DemoWindow),
    answerBoxes(),
    ballsInAnswerBoxes(),
    questions("../QuestionAPI/testFile.csv")
{
    ui->setupUi(this);


    // CONNECTIONS
    connect(ui->fireButton, &QPushButton::pressed, this, &DemoWindow::spawnCannonball);
    connect(ui->angleSlider, &QSlider::sliderMoved, this, &DemoWindow::changeAngle);
    connect(ui->velocitySlider, &QSlider::sliderMoved, this, &DemoWindow::changeVelocity);
    connect(ui->massSlider, &QSlider::sliderMoved, this, &DemoWindow::changeDensity);

    connect(this, &DemoWindow::updateShots, ui->scoreDisplayLabel, &QLabel::setText);
    connect(this, &DemoWindow::updateMessageBox, ui->messageBox, &QLabel::setText);
    connect(this, &DemoWindow::updateLevelBox, ui->levelLabel, &QLabel::setText);

    spriteTimer.setInterval(40);
    connect(&spriteTimer, &QTimer::timeout, this, &DemoWindow::updateSprites);

    // Print the box number when it is hit (for debugging; delete this eventually).
    connect(this, &DemoWindow::answerBoxHit, this, [=] (int box) { std::cout << box << std::endl; });
    connect(this, &DemoWindow::answerBoxHit, this, &DemoWindow::checkCorrectness);

    velocity = 20;
    angle[0] = cos(ui->angleSlider->value() * 3.141f / 180.0f);
    angle[1] = sin(ui->angleSlider->value() * 3.141f / 180.0f);
    density = 1;



    buildLevel1();
    buildLevel2();
    //startQuestion();
    questionIndex = 0;
    startQuestion();

    spriteTimer.start();
}

DemoWindow::~DemoWindow()
{
    delete ui;
    delete sprite;

    for (sf::Sprite* spritePtr : answerBoxes)
        delete spritePtr;
}


void DemoWindow::buildLevel1()
{
    // CONSTRUCT LEVELS--------
    // General process is: 1) Construct level, 2) Load its textures, 3) Add elements
    // Level 1:

    Level* level1 = new Level(-2.0f, 0.04f, 64.0f);

    // Texture preparation and loading
    //++++
    QVector<std::string> imgPaths = {
        "../Images/coinSprite1.png",
        "../Images/coinSprite2.png",
        "../Images/coinSprite3.png",
        "../Images/coinSprite4.png",
        "../Images/blueBlock.png",
        "../Images/SpringBlocks/springGroundWide.png",
        "../Images/SpringBlocks/springBlock2.png",
        "../Images/SpringBlocks/springBlock2Short.png",
        "../Images/SpringBlocks/springTree.png",
        "../Images/SpringBlocks/springTreeTop.png",
        "../Images/SpringBlocks/springTreeMiddle.png",
        "../Images/SpringBlocks/springTreeTrunk.png",
        "../Images/SpringBlocks/springTreeBottom.png",
        "../Images/SpringBlocks/springBlock2Top.png",
        "../Images/SpringBlocks/springBlock2Part.png",
        "../Images/SpringBlocks/springBlock2Btm.png",
        "../Images/cannon1.png",
        "../Images/redBlock.png",
    };

    for (std::string path : imgPaths) {
        sf::Texture temp;
        if (!temp.loadFromFile(path))
            throw "EXIT_FAILURE";
        else
            textures.push_back(temp);
    }

    for (sf::Texture tex : textures) {
        tex.setSmooth(true);
    }

    level1->loadTextures(textures);
    //++++


    // PROBABLY CREATE FUNCTIONS FOR COMMON OBJECTS LIKE I DID WITH THE TREES
    // pyramid of blue blocks
    // bottom level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,496,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,512,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,528,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,560,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,576,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,592,250, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,250, b2Vec2(0,0), 1, 4);
    // 2nd level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,496,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,512,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,528,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,560,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,576,200, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,592,200, b2Vec2(0,0), 1, 4);
    // 3rd level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,512,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,528,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,560,150, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,576,150, b2Vec2(0,0), 1, 4);
    // 4th level
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,528,100, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,100, b2Vec2(0,0), 1, 4);
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,560,100, b2Vec2(0,0), 1, 4);
    // top of pyramid
    level1->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,50, b2Vec2(0,0), 1, 4);


    // pyramid of red blocks
    // bottom level
    level1->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,80, b2Vec2(0,0), 1, 17);
    level1->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,80, b2Vec2(0,0), 1, 17);
    level1->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,80, b2Vec2(0,0), 1, 17);
    level1->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,322,50, b2Vec2(0,0), 1, 17);
    level1->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,338,50, b2Vec2(0,0), 1, 17);
    level1->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,30, b2Vec2(0,0), 1, 17);

    // ground
    level1->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);

    // build a tree from its parts. 2nd parameter is the x position to build
    assembleShortTree(level1, 380);
    assembleMediumTree(level1, 220);
    assembleTallTree(level1, 250);

    // build block/wall structure
    assembleSmallTower(level1, 160);
    assembleMediumTower(level1, 650);
    assembleTallTower(level1, 330);


    level1->setLevelSpeed(6);
    level1->setCannonLocation(b2Vec2(25, 290));
    levels.push_back(level1);

    // repeat process for further levels
    // ------------------------


    spriteSwapIdx = 0;

    // Music stuff ++
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }
    //music.play();
    // ++


    // Add current level sprites to the canvas
    currentLevel = levels[currentLvlInd];
    for (sf::Sprite* s : currentLevel->sprites)
    {
        ui->canvas->addSprite(s);
    }
    emit updateLevelBox("Level " + QString::number(currentLvlInd + 1));

    ui->canvas->setBackdrop("../Images/springBckgrnd.png");
    setupAnswerBoxes();

    // creating with the cannon without box2d
    cannon = new sf::Sprite(textures[16]);
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(25, 290);
    // adding it to the canvas sprites
    ui->canvas->addSprite(cannon);


}

void DemoWindow::buildLevel2()
{

    Level* level2 = new Level(-2.0f, 0.04f, 64.0f);

    QVector<std::string> imgPaths = {
        "../Images/coinSprite1.png",
        "../Images/coinSprite2.png",
        "../Images/coinSprite3.png",
        "../Images/coinSprite4.png",
        "../Images/blueBlock.png",
        "../Images/SpringBlocks/springGroundWide.png",
        "../Images/SpringBlocks/springBlock2.png",
        "../Images/SpringBlocks/springBlock2Short.png",
        "../Images/SpringBlocks/springTree.png",
        "../Images/SpringBlocks/springTreeTop.png",
        "../Images/SpringBlocks/springTreeMiddle.png",
        "../Images/SpringBlocks/springTreeTrunk.png",
        "../Images/SpringBlocks/springTreeBottom.png",
        "../Images/SpringBlocks/springBlock2Top.png",
        "../Images/SpringBlocks/springBlock2Part.png",
        "../Images/SpringBlocks/springBlock2Btm.png",
        "../Images/cannon1.png",
        "../Images/redBlock.png",
    };

    textures.clear();

    for (std::string path : imgPaths) {
        sf::Texture temp;
        if (!temp.loadFromFile(path))
            throw "EXIT_FAILURE";
        else
            textures.push_back(temp);
    }

    for (sf::Texture tex : textures) {
        tex.setSmooth(true);
    }

    level2->loadTextures(textures);


    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            level2->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,(110 * y) + 144 + (16 * x),150, b2Vec2(0,0), 1, 4);

        }
        for(int x = 0; x < 2; x++)
        {
            level2->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,(110 * y) + 152 + (16 * x),120, b2Vec2(0,0), 1, 4);

        }
        for(int x = 0; x < 1; x++)
        {
            level2->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,(110 * y) + 160 + (16 * x),100, b2Vec2(0,0), 1, 4);

        }
    }

    assembleMediumTower(level2, 160);
    assembleMediumTower(level2, 270);
    assembleMediumTower(level2, 380);
    assembleMediumTower(level2, 490);
    assembleMediumTower(level2, 600);

    QVector<b2Vec2> positions;
    positions.append(b2Vec2(170,250));
    positions.append(b2Vec2(280,250));
    positions.append(b2Vec2(390,250));
    positions.append(b2Vec2(610,250));

    level2->setAnswerBoxPositions(positions);

    level2->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);

    level2->setLevelSpeed(6);
    level2->setCannonLocation(b2Vec2(50, 290));
    levels.push_back(level2);

    // Music stuff ++
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }
    //music.play();
    // ++


    currentLevel = levels[0];
    for (sf::Sprite* s : currentLevel->sprites)
    {
        ui->canvas->addSprite(s);
    }

    ui->canvas->setBackdrop("../Images/springBckgrnd.png");
    //setupAnswerBoxes();



    cannon = new sf::Sprite(textures[16]);
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(50, 290);
    //adding it to the canvas sprites
    ui->canvas->addSprite(cannon);
}

void DemoWindow::buildLevel3()
{

}

void DemoWindow::buildLevel4()
{
    // CONSTRUCT LEVELS--------
        // General process is: 1) Construct level, 2) Load its textures, 3) Add elements
        // Level 1:
        Level* level4 = new Level(-2.0f, 0.04f, 64.0f);

        // Texture preparation and loading
        //++++
        QVector<std::string> imgPaths = {
            "../Images/coinSprite1.png",
            "../Images/coinSprite2.png",
            "../Images/coinSprite3.png",
            "../Images/coinSprite4.png",
            "../Images/blueBlock.png",
            "../Images/SpringBlocks/springGroundWide.png",
            "../Images/SpringBlocks/springBlock2.png",
            "../Images/SpringBlocks/springBlock2Short.png",
            "../Images/SpringBlocks/springTree.png",
            "../Images/SpringBlocks/springTreeTop.png",
            "../Images/SpringBlocks/springTreeMiddle.png",
            "../Images/SpringBlocks/springTreeTrunk.png",
            "../Images/SpringBlocks/springTreeBottom.png",
            "../Images/SpringBlocks/springBlock2Top.png",
            "../Images/SpringBlocks/springBlock2Part.png",
            "../Images/SpringBlocks/springBlock2Btm.png",
            "../Images/cannon1.png",
            "../Images/redBlock.png",
        };

        for (std::string path : imgPaths) {
            sf::Texture temp;
            if (!temp.loadFromFile(path))
                throw "EXIT_FAILURE";
            else
                textures.push_back(temp);
        }

        for (sf::Texture tex : textures) {
            tex.setSmooth(true);
        }

        level4->loadTextures(textures);
        //++++l


        // PROBABLY CREATE FUNCTIONS FOR COMMON OBJECTS LIKE I DID WITH THE TREES
        // pyramid of blue blocks
        // bottom level
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,370, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,370, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,370, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,340, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,340, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,340, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,310, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,310, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,310, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,280, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,280, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,280, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,250, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,250, b2Vec2(0,0), 1, 4);
        level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,250, b2Vec2(0,0), 1, 4);

        // Wall of red blocks
        // bottom level
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,230, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,230, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,230, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,200, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,200, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,200, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,170, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,170, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,170, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,140, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,140, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,140, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,110, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,110, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,110, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,80, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,80, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,80, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,50, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,50, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,50, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,30, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,30, b2Vec2(0,0), 1, 17);
        level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,30, b2Vec2(0,0), 1, 17);
        // ground
        level4->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);

        // build a tree from its parts. 2nd parameter is the x position to build
        assembleShortTree(level4, 420);

        // build block/wall structure
        assembleSmallTower(level4, 360);


        level4->setLevelSpeed(6);
        level4->setCannonLocation(b2Vec2(25, 290));
        levels.push_back(level4);

        // repeat process for further levels
        // ------------------------
        // ++

        QVector<b2Vec2> boxPositions;
        boxPositions.append(b2Vec2(600, 50));
        boxPositions.append(b2Vec2(0, 120));
        boxPositions.append(b2Vec2(0, 190));
        boxPositions.append(b2Vec2(0, 260));

        level4->setAnswerBoxPositions(boxPositions);

}

void DemoWindow::buildLevel5()
{
    Level* level = new Level(-2.0f, 0.04f, 64.0f);

    // Texture preparation and loading
    //++++
    QVector<std::string> imgPaths = {
        "../Images/coinSprite1.png",
        "../Images/coinSprite2.png",
        "../Images/coinSprite3.png",
        "../Images/coinSprite4.png",
        "../Images/blueBlock.png",
        "../Images/SpringBlocks/springGroundWide.png",
        "../Images/SpringBlocks/springBlock2.png",
        "../Images/SpringBlocks/springBlock2Short.png",
        "../Images/SpringBlocks/springTree.png",
        "../Images/SpringBlocks/springTreeTop.png",
        "../Images/SpringBlocks/springTreeMiddle.png",
        "../Images/SpringBlocks/springTreeTrunk.png",
        "../Images/SpringBlocks/springTreeBottom.png",
        "../Images/SpringBlocks/springBlock2Top.png",
        "../Images/SpringBlocks/springBlock2Part.png",
        "../Images/SpringBlocks/springBlock2Btm.png",
        "../Images/cannon1.png",
        "../Images/redBlock.png",
    };

    for (std::string path : imgPaths) {
        sf::Texture temp;
        if (!temp.loadFromFile(path))
            throw "EXIT_FAILURE";
        else
            textures.push_back(temp);
    }

    for (sf::Texture tex : textures) {
        tex.setSmooth(true);
    }

    level->loadTextures(textures);

    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,330,115, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,370,115, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,330,100, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,370,100, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,335,85, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,365,85, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,340,70, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,360,70, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,340,55, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,360,55, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,315,115, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,385,115, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,315,100, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,385,100, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,320,85, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,380,85, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,325,70, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,375,70, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,325,55, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,375,55, b2Vec2(0,0), 1, 4);

    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,300, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,300, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,280, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,280, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,260, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,260, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,240, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,240, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,220, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,220, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,200, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,200, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,180, b2Vec2(0,0), 1, 4);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,180, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,160, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,160, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,140, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,140, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,120, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,120, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,100, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,100, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,80, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,80, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,60, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,60, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,40, b2Vec2(0,0), 100, 17);
    level->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,40, b2Vec2(0,0), 100, 17);


    // ground
    level->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);

    // build a tree from its parts. 2nd parameter is the x position to build
    //assembleShortTree(level, 380);
    assembleMediumTree(level, 75);
    assembleTallTree(level, 150);

    // build block/wall structure
    //assembleSmallTower(level, 160);
    //assembleMediumTower(level, 650);
    assembleTallTower(level, 330);
    assembleTallTower(level, 375);


    level->setLevelSpeed(6);
    level->setCannonLocation(b2Vec2(350, 115));
    levels.push_back(level);

    // repeat process for further levels
    // ------------------------


    spriteSwapIdx = 0;

    // Music stuff ++
    if (!music.openFromFile("../Imperial_March.ogx")) {
        throw "EXIT_FAILURE";
    }
    //music.play();
    // ++


    // Add current level sprites to the canvas
    currentLevel = levels[0];
    for (sf::Sprite* s : currentLevel->sprites)
    {
        ui->canvas->addSprite(s);
    }

    ui->canvas->setBackdrop("../Images/springBckgrnd.png");
    setupAnswerBoxes();

    //creating with the cannon without box2d
    cannon = new sf::Sprite(textures[16]);
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(350, 115);
     //adding it to the canvas sprites
    ui->canvas->addSprite(cannon);
}


void DemoWindow::assembleShortTree(Level* level1, float32 posX)
{
    level1->createCircleNew(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 267, 9);    //leaves
    level1->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 284, 10); //middle
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 291, 11); //trunk
    level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 298, 11); //trunk
    level1->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::assembleMediumTree(Level* level1, float32 posX)
{
    level1->createCircleNew(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 253, 9);    //leaves
    level1->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 270, 10); //middle
    // trunk loop
    int j = 277;
    for(int i = 0; i < 4; i++)
    {
        level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, j, 11);
        j+=7;
    }
    level1->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::assembleTallTree(Level* level1, float32 posX)
{
    level1->createCircleNew(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 232, 9);    //leaves
    level1->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 249, 10); //middle
    // trunk loop
    int j = 256;
    for(int i = 0; i < 7; i++)
    {
        level1->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, j, 11);
        j+=7;
    }
    level1->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::assembleSmallTower(Level* level1, float32 posX)
{
    level1->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, posX, 264, 13);    // top
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 286, 14);    // middle
    level1->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, posX, 303, 15);    // bottom
}

void DemoWindow::assembleMediumTower(Level* level1, float32 posX)
{
    level1->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, posX, 200, 13);    // top
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 222, 14);    // middle
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 254, 14);    // middle
    level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 286, 14);    // middle
    level1->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, posX, 303, 15);    // bottom
}

void DemoWindow::assembleTallTower(Level* level1, float32 posX)
{
    level1->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, posX, 136, 13);    // top
    // loop for middle pieces
    int blockYPos = 158;
    for(int i = 0; i < 5; i++)
    {
        level1->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, blockYPos, 14);    // middle
        blockYPos += 32;
    }
    level1->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, posX, 303, 15);    // bottom
}

void DemoWindow::setupAnswerBoxes()
{
    answerTextures = std::vector<sf::Texture>(4);
    sf::Texture boxTextureA;
    sf::Texture boxTextureB;
    sf::Texture boxTextureC;
    sf::Texture boxTextureD;

    if (!answerTextures[0].loadFromFile("../Images/QuestionRelated/boxA.png"))
        throw "image not found.";
    if (!answerTextures[1].loadFromFile("../Images/QuestionRelated/boxB.png"))
        throw "image not found.";
    if (!answerTextures[2].loadFromFile("../Images/QuestionRelated/boxC.png"))
        throw "image not found.";
    if (!answerTextures[3].loadFromFile("../Images/QuestionRelated/boxD.png"))
        throw "image not found.";

    // Load the textures into the boxes.
    answerBoxes.push_back(new sf::Sprite(answerTextures[0]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[1]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[2]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[3]));

    // Place the boxes in the level.
    for (uint16_t idx = 0; idx < 4; idx++) {
        answerBoxes[idx]->scale(float(0.6), float(0.6));
        answerBoxes[idx]->setPosition(600, 50 + 70 * idx);
        answerBoxes[idx]->setOrigin(50, 50);
        ui->canvas->addSprite(answerBoxes[idx]);
    }
}

int DemoWindow::answerBoxIndex(int x, int y)
{
    sf::FloatRect bounds = answerBoxes[0]->getGlobalBounds();
    if (y >= bounds.top && x >= bounds.left && y - bounds.top <= bounds.height && x - bounds.left <= bounds.width)
        return 0;

    bounds = answerBoxes[1]->getGlobalBounds();
    if (y >= bounds.top && x >= bounds.left && y - bounds.top <= bounds.height && x - bounds.left <= bounds.width)
        return 1;

    bounds = answerBoxes[2]->getGlobalBounds();
    if (y >= bounds.top && x >= bounds.left && y - bounds.top <= bounds.height && x - bounds.left <= bounds.width)
        return 2;

    bounds = answerBoxes[3]->getGlobalBounds();
    if (y >= bounds.top && x >= bounds.left && y - bounds.top <= bounds.height && x - bounds.left <= bounds.width)
        return 3;

    return -1;
}

void DemoWindow::nextLevel() {
    if (currentLvlInd < levels.size()-1) // There are more levels to go
    {
        numShots = 0;
        currentLevel = levels[++currentLvlInd];
        ui->canvas->clear();
        for (sf::Sprite* s : currentLevel->sprites)
        {
            ui->canvas->addSprite(s);
        }
        uint idx = 0;
        for (b2Vec2 pos : currentLevel->getAnswerBoxPositions()) {
            answerBoxes[idx]->setPosition(pos.x, pos.y);
            idx++;
        }
        emit updateLevelBox("Level " + QString::number(currentLvlInd + 1));
    }
    else // Game has been beaten
    {
        emit updateMessageBox("You have beaten the game. \nTotal shots: " + QString::number(totalShots));
    }

}

// SLOTS
void DemoWindow::checkCorrectness(int boxNum)
{
    if (boxNum == 0) { // If correct answer
        emit updateMessageBox("Correct answer hit!");
        nextLevel();
    }
    else {
        emit updateMessageBox("Wrong answer hit!");
    }
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
        s->setRotation(currentLevel->bodies[index]->GetAngle()*57.2958f);

        // Deal with hitting the answers (right or wrong).
        if (ballsInAnswerBoxes.find(index) != ballsInAnswerBoxes.end())
        {
            int boxIndex = answerBoxIndex(static_cast<int>(pos.x), static_cast<int>(-1 * pos.y));
            if (ballsInAnswerBoxes[index] && boxIndex < 0)
                ballsInAnswerBoxes[index] = false;

            else if (!ballsInAnswerBoxes[index] && boxIndex >= 0) {
                answerBoxHit(boxIndex);
                ballsInAnswerBoxes[index] = true;
            }
        }
    }
    spriteSwapIdx++;
}

void DemoWindow::spawnCannonball()
{
    totalShots++;
    emit updateShots(QString::number(++numShots));
    currentLevel->fireCannonball(b2Vec2(angle[0] * velocity, angle[1] * velocity), density);
    ui->canvas->addSprite(currentLevel->sprites[currentLevel->sprites.size()-1]);
    ballsInAnswerBoxes[currentLevel->sprites.size() - 1] = false;
}

void DemoWindow::changeAngle()
{
    angle[0] = cos(ui->angleSlider->value() * 3.141f / 180.0f);
    angle[1] = sin(ui->angleSlider->value() * 3.141f / 180.0f);
    cannon->setRotation(ui->angleSlider->value() * - 1);
}

void DemoWindow::changeVelocity()
{
    velocity = ui->velocitySlider->value() / 10.0f;
//    std::cout << velocity << std::endl;
}

void DemoWindow::changeDensity()
{
    density = ui->massSlider->value();
}

void DemoWindow::startQuestion() {
    QuestionModel::Question q = questions.Questions()[questionIndex];
    currentQuestion = questions.ShuffleAnswers(q);

    ui->questionLabel->setText(QString::fromStdString(currentQuestion.question));
    ui->answerLabelA->setText(QString::fromStdString("(A) "+currentQuestion.answers[0]));
    ui->answerLabelB->setText(QString::fromStdString("(B) "+currentQuestion.answers[1]));
    ui->answerLabelC->setText(QString::fromStdString("(C) "+currentQuestion.answers[2]));
    ui->answerLabelD->setText(QString::fromStdString("(D) "+currentQuestion.answers[3]));

}

bool DemoWindow::checkAnswer(int playerAnswer) {
    return (playerAnswer == currentQuestion.correctAnswer);
}
