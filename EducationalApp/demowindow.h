#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QTimer>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "level.h"
#include "QuestionAPI.h"

namespace Ui {
class DemoWindow;
}

class DemoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DemoWindow(QWidget *parent = nullptr);
    ~DemoWindow();

private:
    Ui::DemoWindow *ui;
    QTimer spriteTimer;
//    sf::Sprite* sprite;
    int spriteSwapIdx;
    std::vector<sf::Texture> textures;
    std::vector<sf::Texture> answerTextures;
    std::vector<sf::Sprite*> answerBoxes;
    QVector<Level*> levels;
    //QuestionModel questions;
    sf::Music music;
    sf::SoundBuffer soundBuffer;
    sf::Sound shootSound;
    Level* currentLevel;
//    std::map<int, bool> ballsInAnswerBoxes;
    int nonBallBodies;
    int numShots = 0;
    int totalShots = 0;
    int currentLvlInd = -1;
    sf::Sprite* cannon;
    sf::Sprite* tankTrooper;
//    std::vector<bool> bodiesDeleted;
    float angle[3];
    float velocity;
    float density;
    QuestionModel questions;
    int questionIndex;
    QuestionModel::ShuffledQuestion currentQuestion;
    sf::Texture troopTex;
    bool soundIsOn = true;

    void buildLevel1();
    void buildLevel2();
    void buildLevel3();
    void buildLevel4();
    void buildLevel5();

    void setupGrayAnswerBoxes();
    void setupIceAnswerBoxes();
    ///
    /// \brief answerBoxIndex
    /// \param x
    /// \param y
    /// \return
    ///
    /// Returns -1 if the coordinate is not in an answer box, or the index of the answer box if it
    /// is (i.e. 0 for box A, 3 for box D).
    int answerBoxIndex(int x, int y);
    void buildBluePyramid(Level* targetLevel,int baseSize, float32 xStartPos, float32 yStartPos);
    void buildRedPyramid(Level* targetLevel,int baseSize, float32 xStartPos, float32 yStartPos);
    void assembleShortTree(Level* targetLevel, float32 posX);
    void assembleMediumTree(Level* targetLevel, float32 posX);
    void assembleTallTree(Level* targetLevel, float32 posX);
    void assembleSmallTower(Level* targetLevel, float32 posX);
    void assembleMediumTower(Level* targetLevel, float32 posX);
    void assembleTallTower(Level* targetLevel, float32 posX);
    void nextLevel();

public slots:
    void checkCorrectness(int boxNum);
    void updateSprites();
    void spawnCannonball();
    void changeVelocity();
    void changeAngle();
    void changeDensity();

    void startQuestion();
    bool checkAnswer(int playerAnswer);

    void toggleSound();
    void quitGame();

    void restartGame();
    void restartLevel();


signals:
    ///
    /// \brief answerBoxHit
    /// \param boxIndex
    ///
    /// Called when a cannonball enters one of the answer boxes. The boxIndex corresponds to the
    /// answer: 0 for box A, 1 for box B, etc.
    void answerBoxHit(int boxIndex);
    void updateShots(QString shots);
    void updateMessageBox(QString msg);
    void updateLevelBox(QString lvl);
};

#endif // DEMOWINDOW_H
