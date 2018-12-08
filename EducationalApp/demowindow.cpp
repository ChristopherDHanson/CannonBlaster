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

    // Make the game respond to hitting answer boxes with a cannonball.
    connect(this, &DemoWindow::answerBoxHit, this, &DemoWindow::checkCorrectness);

    velocity = 20;
    angle[0] = cos(ui->angleSlider->value() * 3.141f / 180.0f);
    angle[1] = sin(ui->angleSlider->value() * 3.141f / 180.0f);
    density = 1;


    if (!troopTex.loadFromFile("../Images/tankTrooper.png"))
        throw "EXIT_FAILURE";
    else {
        tankTrooper = new sf::Sprite(troopTex);
        tankTrooper->setOrigin(troopTex.copyToImage().getSize().x/2, troopTex.copyToImage().getSize().y/2);
    }

    buildLevel1();
    buildLevel2();
    buildLevel3();
    buildLevel4();
    buildLevel5();
    nextLevel();
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
    // General process is: 1) Construct level, 2) Load its textures, 3) Add elements
    // Level 1:

    Level* level1 = new Level(-2.0f, 0.04f, 64.0f);

    // Texture preparation and loading
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
        "../Images/cannon2.png",
        "../Images/redBlock.png"
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

    // ground
    level1->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);
    // background
    level1->setBackground("../Images/springBckgrndWide.png");

    // build landscape
    // pyramid of blue blocks
    buildBluePyramid(level1, 9, 410, 250);

    // pyramid of red blocks
    buildRedPyramid(level1, 3, 314, 80);

    // build a tree from its parts. 2nd parameter is the x position to build
    assembleShortTree(level1, 380);
    assembleMediumTree(level1, 220);
    assembleTallTree(level1, 250);

    // build block/wall structure
    assembleSmallTower(level1, 160);
    assembleMediumTower(level1, 650);
    assembleTallTower(level1, 330);

    // needs to occur only in first level method
    setupBrownAnswerBoxes();

    // set answer box positions
    QVector<b2Vec2> positions;
    positions.push_back(b2Vec2(580,40));
    positions.push_back(b2Vec2(580,110));
    positions.push_back(b2Vec2(580,180));
    positions.push_back(b2Vec2(580,250));
    level1->setAnswerBoxPositions(positions);


    level1->setLevelSpeed(6);   // level iteration speed

    //cannon
    level1->setCannonLocation(b2Vec2(40, 295));
    cannon = new sf::Sprite(*level1->getTexturePtr(16));
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(40, 295);
    level1->setCannon(cannon);

    // set background music
    level1->setMusicPath("../Audio/chiptune1.ogg");

    //music.play();

    levels.push_back(level1);
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
        "../Images/cannon2.png",
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

    // ground
    level2->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);
    // background
    level2->setBackground("../Images/springBckgrndWide.png");
    // build landscape
    buildRedPyramid(level2, 3, 144, 150);
    buildRedPyramid(level2, 3, 254, 150);
    buildRedPyramid(level2, 3, 364, 150);
    buildRedPyramid(level2, 3, 474, 150);
    buildRedPyramid(level2, 3, 584, 150);
    assembleMediumTower(level2, 160);
    assembleMediumTower(level2, 270);
    assembleMediumTower(level2, 380);
    assembleMediumTower(level2, 490);
    assembleMediumTower(level2, 600);

    // set answer box positions
    QVector<b2Vec2> positions;
    positions.append(b2Vec2(215,272));
    positions.append(b2Vec2(325,272));
    positions.append(b2Vec2(435,272));
    positions.append(b2Vec2(545,272));
    level2->setAnswerBoxPositions(positions);

    level2->setLevelSpeed(6);   // level iteration speed

    // cannon
    level2->setCannonLocation(b2Vec2(50, 295));
    cannon = new sf::Sprite(*level2->getTexturePtr(16));
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(50, 295);
    level2->setCannon(cannon);

    // Set background music
    level2->setMusicPath("../Audio/chiptune1.ogg");

    //music.play();

    levels.push_back(level2);
}

void DemoWindow::buildLevel3()
{
    Level* level3 = new Level(-2.0f, 0.04f, 64.0f);

    // Texture preparation and loading
    QVector<std::string> imgPaths = {
        "../Images/coinSprite1.png",
        "../Images/coinSprite2.png",
        "../Images/coinSprite3.png",
        "../Images/coinSprite4.png",
        "../Images/blueBlock.png",
        "../Images/WinterBlocks/winterGroundWide.png",
        "../Images/WinterBlocks/winterBlock2.png",
        "../Images/WinterBlocks/winterBlock2Short.png",
        "../Images/WinterBlocks/winterTree.png",
        "../Images/WinterBlocks/winterTreeTop.png",
        "../Images/WinterBlocks/winterTreeMiddle.png",
        "../Images/WinterBlocks/winterTreeTrunk.png",
        "../Images/WinterBlocks/winterTreeBtm.png",
        "../Images/WinterBlocks/winterBlock2Top.png",
        "../Images/WinterBlocks/winterBlock2Part.png",
        "../Images/WinterBlocks/winterBlock2Btm.png",
        "../Images/cannon2.png",
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

    level3->loadTextures(textures);



    // ground
    level3->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);

    // background
    level3->setBackground("../Images/winterBckgrndWide.png");
    // build block/wall structure
    //assembleSmallTower(level3, 160);
    assembleTallTower(level3, 650);
    assembleTallTower(level3, 45);
    assembleTallTower(level3, -3);
    assembleMediumTower(level3, 93);
    assembleSmallTower(level3, 350);
    assembleMediumTree(level3, 150);
    assembleShortTree(level3, 190);
    assembleTallTree(level3, 230);
    assembleMediumTree(level3,270);
    assembleShortTree(level3, 310);
    assembleShortTree(level3, 390);
    assembleTallTree(level3, 430);
    assembleMediumTree(level3,470);


//    setupIceAnswerBoxes();

    QVector<b2Vec2> positions;
    positions.push_back(b2Vec2(580,40));
    positions.push_back(b2Vec2(580,110));
    positions.push_back(b2Vec2(580,180));
    positions.push_back(b2Vec2(580,250));
    level3->setAnswerBoxPositions(positions);

    level3->setLevelSpeed(6);

    // cannon
    level3->setCannonLocation(b2Vec2(45, 120));
    cannon = new sf::Sprite(*level3->getTexturePtr(16));
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(45, 120);
    level3->setCannon(cannon);

    // Set background music
    level3->setMusicPath("../Audio/chiptune1.ogg");

    //music.play();
    // ++

    levels.push_back(level3);
}

void DemoWindow::buildLevel4()
{
        Level* level4 = new Level(-2.0f, 0.04f, 64.0f);

        // Texture preparation and loading
        QVector<std::string> imgPaths = {
            "../Images/coinSprite1.png",
            "../Images/coinSprite2.png",
            "../Images/coinSprite3.png",
            "../Images/coinSprite4.png",
            "../Images/blueBlock.png",
            "../Images/WinterBlocks/winterGroundWide.png",
            "../Images/WinterBlocks/winterBlock2.png",
            "../Images/WinterBlocks/winterBlock2Short.png",
            "../Images/WinterBlocks/winterTree.png",
            "../Images/WinterBlocks/winterTreeTop.png",
            "../Images/WinterBlocks/winterTreeMiddle.png",
            "../Images/WinterBlocks/winterTreeTrunk.png",
            "../Images/WinterBlocks/winterTreeBtm.png",
            "../Images/WinterBlocks/winterBlock2Top.png",
            "../Images/WinterBlocks/winterBlock2Part.png",
            "../Images/WinterBlocks/winterBlock2Btm.png",
            "../Images/cannon2.png",
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

        level4->loadTextures(textures);

        // ground
        level4->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);
        // build landscape
        level4->setBackground("../Images/winterBckgrndWide.png");

        // blue block towers
        for(int i = 0; i < 5; i++)
        {
            level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,480,300 - 30 * i, b2Vec2(0,0), 1, 4);
            level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,544,300 - 30 * i, b2Vec2(0,0), 1, 4);
            level4->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,608,300 - 30 * i, b2Vec2(0,0), 1, 4);
        }

        // Wall of red blocks
        for(int i = 0; i < 8; i++)
        {
            level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,314,230 - 30 * i, b2Vec2(0,0), 1, 17);
            level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,330,230 - 30 * i, b2Vec2(0,0), 1, 17);
            level4->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y,346,230 - 30 * i, b2Vec2(0,0), 1, 17);
        }

        // build a tree from its parts. 2nd parameter is the x position to build
        assembleShortTree(level4, 420);
        assembleMediumTree(level4, 220);
//        assembleShortTree(level4, 320);
        assembleTallTree(level4, 280);

        // build block/wall structure
        assembleSmallTower(level4, 330);


        QVector<b2Vec2> boxPositions;
        boxPositions.append(b2Vec2(200, 50));
        boxPositions.append(b2Vec2(300, 50));
        boxPositions.append(b2Vec2(400, 50));
        boxPositions.append(b2Vec2(500, 50));
        level4->setAnswerBoxPositions(boxPositions);

        level4->setLevelSpeed(6);


        level4->setCannonLocation(b2Vec2(45, 295));
        cannon = new sf::Sprite(*level4->getTexturePtr(16));
        cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
        cannon->setPosition(45, 295);
        level4->setCannon(cannon);
        // Set background music
        level4->setMusicPath("../Audio/chiptune1.ogg");

        //music.play();

        levels.push_back(level4);

}

void DemoWindow::buildLevel5()
{
    Level* level5 = new Level(-2.0f, 0.04f, 64.0f);

    // Texture preparation and loading
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
        "../Images/cannon2.png",
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

    level5->loadTextures(textures);

    // ground
    level5->createBox(textures[5].copyToImage().getSize().x,textures[5].copyToImage().getSize().y, 346, 320, 5);
    // background
    level5->setBackground("../Images/springBckgrndWide.png");


    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,330,115, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,370,115, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,330,100, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,370,100, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,335,85, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,365,85, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,340,70, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,360,70, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,340,55, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,360,55, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,315,115, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,385,115, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,315,100, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,385,100, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,320,85, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,380,85, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,325,70, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,375,70, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,325,55, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,375,55, b2Vec2(0,0), 1, 4);

    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,300, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,300, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,280, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,280, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,260, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,260, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,240, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,240, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,220, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,220, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,200, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,200, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,180, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,180, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,160, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,160, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,140, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,140, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,120, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,120, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,100, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,100, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,80, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,80, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,60, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,60, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,40, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,40, b2Vec2(0,0), 100, 17);


//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,316,115, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,332,115, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,316,100, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,332,100, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,325,70, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,325,55, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,330,100, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,335,85, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,340,70, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,340,55, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,360,70, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,360,55, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,365,85, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,370,115, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,370,100, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,375,70, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,375,55, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,380,85, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,385,115, b2Vec2(0,0), 1, 4);
//    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,385,100, b2Vec2(0,0), 1, 4);







    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,300, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,300, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,280, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,280, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,260, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,260, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,240, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,240, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,220, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,220, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,200, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,200, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,180, b2Vec2(0,0), 1, 4);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,180, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,160, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,160, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,140, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,140, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,120, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,120, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,100, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,100, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,80, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,80, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,60, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,60, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,530,40, b2Vec2(0,0), 100, 17);
    level5->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y,545,40, b2Vec2(0,0), 100, 17);


    // build a tree from its parts. 2nd parameter is the x position to build
    //assembleShortTree(level, 380);
    assembleMediumTree(level5, 75);
    assembleTallTree(level5, 150);

    // build block/wall structure
    //assembleSmallTower(level, 160);
    //assembleMediumTower(level, 650);
    assembleTallTower(level5, 330);
    assembleTallTower(level5, 375);


    // set answer box positions
    QVector<b2Vec2> positions;
    positions.append(b2Vec2(215,272));
    positions.append(b2Vec2(325,272));
    positions.append(b2Vec2(435,272));
    positions.append(b2Vec2(545,272));
    level5->setAnswerBoxPositions(positions);

    level5->setLevelSpeed(6);   // level iteration speed

    // cannon
    level5->setCannonLocation(b2Vec2(350, 115));
    cannon = new sf::Sprite(*level5->getTexturePtr(16));
    cannon->setOrigin(textures[16].copyToImage().getSize().x/2, textures[16].copyToImage().getSize().y/2);
    cannon->setPosition(350, 115);
    level5->setCannon(cannon);

    // Set background music
    level5->setMusicPath("../Audio/chiptune1.ogg");

    //music.play();

    levels.push_back(level5);
}


// use for shorter pyramids. Shorter than the base
void DemoWindow::buildBluePyramid(Level* targetLevel, int baseSize, float32 xStartPos, float32 yStartPos)
{
    float32 xPos = xStartPos;
    float32 yPos = yStartPos;
    int crrntLvlNumBlcks = baseSize;
    int pyramidHeight = baseSize/2 + baseSize%2;
    for(int i = 0; i < pyramidHeight; i++)
    {
        float32 crrntBlockXPos = xPos;
        for(int j = 0; j < crrntLvlNumBlcks; j++)
        {
            targetLevel->createDynamicBox(textures[4].copyToImage().getSize().x,textures[4].copyToImage().getSize().y, crrntBlockXPos, yPos, b2Vec2(0,0), 1, 4);
            crrntBlockXPos +=16;
        }
        yPos -= 30;
        xPos += 16;
        crrntLvlNumBlcks -= 2;
    }
}

// use for taller pyramids. As tall as the base
void DemoWindow::buildRedPyramid(Level* targetLevel, int baseSize, float32 xStartPos, float32 yStartPos)
{
    float32 xPos = xStartPos;
    float32 yPos = yStartPos;
    int crrntLvlNumBlcks = baseSize;
    for(int i = 0; i < baseSize; i++)
    {
        float32 crrntBlockXPos = xPos;
        for(int j = 0; j < crrntLvlNumBlcks; j++)
        {
            targetLevel->createDynamicBox(textures[17].copyToImage().getSize().x,textures[17].copyToImage().getSize().y, crrntBlockXPos, yPos, b2Vec2(0,0), 1, 17);
            crrntBlockXPos +=16;
        }
        yPos -= 30;
        xPos += 8;
        crrntLvlNumBlcks--;
    }
}

void DemoWindow::assembleShortTree(Level* targetLevel, float32 posX)
{
    targetLevel->createCircleNew(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 267, 9);    //leaves
    targetLevel->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 284, 10); //middle
    targetLevel->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 291, 11); //trunk
    targetLevel->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, 298, 11); //trunk
    targetLevel->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::assembleMediumTree(Level* targetLevel, float32 posX)
{
    targetLevel->createCircleNew(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 253, 9);    //leaves
    targetLevel->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 270, 10); //middle
    // trunk loop
    int j = 277;
    for(int i = 0; i < 4; i++)
    {
        targetLevel->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, j, 11);
        j+=7;
    }
    targetLevel->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::assembleTallTree(Level* targetLevel, float32 posX)
{
    targetLevel->createCircleNew(textures[9].copyToImage().getSize().x,textures[9].copyToImage().getSize().y, posX, 232, 9);    //leaves
    targetLevel->createBox(textures[10].copyToImage().getSize().x,textures[10].copyToImage().getSize().y, posX, 249, 10); //middle
    // trunk loop
    int j = 256;
    for(int i = 0; i < 7; i++)
    {
        targetLevel->createBox(textures[11].copyToImage().getSize().x,textures[11].copyToImage().getSize().y, posX, j, 11);
        j+=7;
    }
    targetLevel->createBox(textures[12].copyToImage().getSize().x,textures[12].copyToImage().getSize().y, posX, 303, 12); //base
}

void DemoWindow::assembleSmallTower(Level* targetLevel, float32 posX)
{
    targetLevel->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, posX, 264, 13);    // top
    targetLevel->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 286, 14);    // middle
    targetLevel->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, posX, 303, 15);    // bottom
}

void DemoWindow::assembleMediumTower(Level* targetLevel, float32 posX)
{
    targetLevel->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, posX, 200, 13);    // top
    targetLevel->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 222, 14);    // middle
    targetLevel->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 254, 14);    // middle
    targetLevel->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, 286, 14);    // middle
    targetLevel->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, posX, 303, 15);    // bottom
}

void DemoWindow::assembleTallTower(Level* targetLevel, float32 posX)
{
    targetLevel->createBox(textures[13].copyToImage().getSize().x,textures[13].copyToImage().getSize().y, posX, 136, 13);    // top
    // loop for middle pieces
    int blockYPos = 158;
    for(int i = 0; i < 5; i++)
    {
        targetLevel->createBox(textures[14].copyToImage().getSize().x,textures[14].copyToImage().getSize().y, posX, blockYPos, 14);    // middle
        blockYPos += 32;
    }
    targetLevel->createBox(textures[15].copyToImage().getSize().x,textures[15].copyToImage().getSize().y, posX, 303, 15);    // bottom
}

void DemoWindow::setupBrownAnswerBoxes()
{
    answerTextures = std::vector<sf::Texture>(4);
    sf::Texture boxTextureA;
    sf::Texture boxTextureB;
    sf::Texture boxTextureC;
    sf::Texture boxTextureD;

    if (!answerTextures[0].loadFromFile("../Images/QuestionRelated/grayAnswerBoxA.png"))
        throw "image not found.";
    if (!answerTextures[1].loadFromFile("../Images/QuestionRelated/grayAnswerBoxB.png"))
        throw "image not found.";
    if (!answerTextures[2].loadFromFile("../Images/QuestionRelated/grayAnswerBoxC.png"))
        throw "image not found.";
    if (!answerTextures[3].loadFromFile("../Images/QuestionRelated/grayAnswerBoxD.png"))
        throw "image not found.";

    // Load the textures into the boxes.
    answerBoxes.push_back(new sf::Sprite(answerTextures[0]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[1]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[2]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[3]));

    sf::FloatRect boxDim;
    // Scale the boxes and put their origins in the center.
    for (uint16_t idx = 0; idx < 4; idx++) {
//        answerBoxes[idx]->scale(float(0.9), float(0.9));
        boxDim = answerBoxes[idx]->getGlobalBounds();
        answerBoxes[idx]->setOrigin(boxDim.width / 2, boxDim.height / 2);
    }
}

void DemoWindow::setupIceAnswerBoxes()
{
    answerTextures = std::vector<sf::Texture>(4);
    sf::Texture boxTextureA;
    sf::Texture boxTextureB;
    sf::Texture boxTextureC;
    sf::Texture boxTextureD;

    if (!answerTextures[0].loadFromFile("../Images/QuestionRelated/iceAnswerBoxA.png"))
        throw "image not found.";
    if (!answerTextures[1].loadFromFile("../Images/QuestionRelated/iceAnswerBoxB.png"))
        throw "image not found.";
    if (!answerTextures[2].loadFromFile("../Images/QuestionRelated/iceAnswerBoxC.png"))
        throw "image not found.";
    if (!answerTextures[3].loadFromFile("../Images/QuestionRelated/iceAnswerBoxD.png"))
        throw "image not found.";

    // Load the textures into the boxes.
    answerBoxes.push_back(new sf::Sprite(answerTextures[0]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[1]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[2]));
    answerBoxes.push_back(new sf::Sprite(answerTextures[3]));

    sf::FloatRect boxDim;
    // Scale the boxes and put their origins in the center.
    for (uint16_t idx = 0; idx < 4; idx++) {
//        answerBoxes[idx]->scale(float(0.9), float(0.9));
        boxDim = answerBoxes[idx]->getGlobalBounds();
        answerBoxes[idx]->setOrigin(boxDim.width / 2, boxDim.height / 2);
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
    spriteTimer.stop();
    if (currentLvlInd < levels.size()-1) // There are more levels to go
    {
        // Update the question.
        if (++questionIndex < questions.Questions().size())
            startQuestion();

        // Update the level (map, objects, etc.).
        numShots = 0;
        currentLevel = levels[++currentLvlInd];
        ui->canvas->removeAllSprites();
        ui->canvas->clear();
        for (sf::Sprite* s : currentLevel->sprites)
        {
            ui->canvas->addSprite(s);
        }
        ui->canvas->setBackdrop(currentLevel->getBackground());
        ui->canvas->addSprite(currentLevel->getCannon());
        tankTrooper->setPosition(sf::Vector2f(currentLevel->getCannon()->getPosition().x - 30, currentLevel->getCannon()->getPosition().y - 3));
        ui->canvas->addSprite(tankTrooper);
        uint idx = 0;
        for (b2Vec2 pos : currentLevel->getAnswerBoxPositions()) {
            answerBoxes[idx]->setPosition(pos.x, pos.y);
            ui->canvas->addSprite(answerBoxes[idx]);
            idx++;
        }
        emit updateLevelBox("Level " + QString::number(currentLvlInd + 1));
        spriteTimer.start();
    }
    else // Game has been beaten
    {
        emit updateMessageBox("You have beaten the game. \nTotal shots: " + QString::number(totalShots));
    }
}

// SLOTS
void DemoWindow::checkCorrectness(int boxNum)
{
    if (checkAnswer(boxNum)) { // If correct answer
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
                emit answerBoxHit(boxIndex);
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
    currentLevel->getCannon()->setRotation(ui->angleSlider->value() * - 1);
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
