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
    questions("../QuestionAPI/testfile.csv")
{
    ui->setupUi(this);


    // CONNECTIONS
    connect(ui->fireButton, &QPushButton::pressed, this, &DemoWindow::spawnCannonball);
    connect(ui->angleSlider, &QSlider::sliderMoved, this, &DemoWindow::changeAngle);
    connect(ui->velocitySlider, &QSlider::sliderMoved, this, &DemoWindow::changeVelocity);
    connect(ui->massSlider, &QSlider::sliderMoved, this, &DemoWindow::changeDensity);

    connect(this, &DemoWindow::updateShots,
                         ui->scoreDisplayLabel, &QLabel::setText);

    spriteTimer.setInterval(40);
    connect(&spriteTimer, &QTimer::timeout, this, &DemoWindow::updateSprites);

    velocity = 20;
    angle[0] = cos(ui->angleSlider->value() * 3.141 / 180);
    angle[1] = sin(ui->angleSlider->value() * 3.141 / 180);
    density = 1;



    buildLevel1();
    //startQuestion();

    spriteTimer.start();

    // Print the box number when it is hit (for debugging; delete this eventually).
    connect(this, &DemoWindow::answerBoxHit, this, [=] (int box) { std::cout << box << std::endl; });
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
    cannon->setPosition(25, 290);
     //adding it to the canvas sprites
    ui->canvas->addSprite(cannon);
}

void DemoWindow::buildLevel2()
{

}

void DemoWindow::buildLevel3()
{

}

void DemoWindow::buildLevel4()
{

}

void DemoWindow::buildLevel5()
{

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


// SLOTS
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
        //s->rotate(1.0);
        //s->setTexture(textures[(spriteSwapIdx / 5) % 4]);
        //std::cout << pos.x << " " <<pos.y << "  \n";
    }

    // Change cannon rotation
    //cannon->setRotation(2);

    spriteSwapIdx++;
}

void DemoWindow::spawnCannonball()
{
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
    currentQuestion = questions.ShuffleAnswers(questions.Questions()[questionIndex]);
    ui->questionLabel->setText(QString::fromStdString(currentQuestion.question));
    ui->answerLabelA->setText(QString::fromStdString("(A) "+currentQuestion.answers[0]));
    ui->answerLabelB->setText(QString::fromStdString("(B) "+currentQuestion.answers[1]));
    ui->answerLabelC->setText(QString::fromStdString("(C) "+currentQuestion.answers[2]));
    ui->answerLabelD->setText(QString::fromStdString("(D) "+currentQuestion.answers[3]));
}

bool DemoWindow::checkAnswer(int playerAnswer) {
    return (playerAnswer == currentQuestion.correctAnswer);
}

