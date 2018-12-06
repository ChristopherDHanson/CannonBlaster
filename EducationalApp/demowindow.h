#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QTimer>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "level.h"

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
    sf::Sprite* sprite;
    int spriteSwapIdx;
    std::vector<sf::Texture> textures;
    std::vector<sf::Texture> nonInteractiveTextures;
    sf::Music music;
    QVector<Level*> levels;
    Level* currentLevel;
    std::vector<sf::Texture> answerTextures;
    std::vector<sf::Sprite*> answerBoxes;
    std::map<int, bool> ballsInAnswerBoxes;

    sf::Sprite* cannon;
    QVector<sf::Sprite*> sprites;
    float angle[3];
    float velocity;
    float density;

    void loadBackground();
    void setupAnswerBoxes();
    ///
    /// \brief answerBoxIndex
    /// \param x
    /// \param y
    /// \return
    ///
    /// Returns -1 if the coordinate is not in an answer box, or the index of the answer box if it
    /// is (i.e. 0 for box A, 3 for box D).
    int answerBoxIndex(int x, int y);

public slots:
    void updateSprites();
    void spawnCannonball();
    void spawnShortTree(Level* level1, float32 posX);
    void spawnMediumTree(Level* level1, float32 posX);
    void spawnTallTree(Level* level1, float32 posX);
    void spawnSmallTower(Level* level1, float32 posX);
    void spawnMediumTower(Level* level1, float32 posX);
    void spawnTallTower(Level* level1, float32 posX);
    void changeVelocity();
    void changeAngle();
    void changeDensity();

signals:
    ///
    /// \brief answerBoxHit
    /// \param boxIndex
    ///
    /// Called when a cannonball enters one of the answer boxes. The boxIndex corresponds to the
    /// answer: 0 for box A, 1 for box B, etc.
    void answerBoxHit(int boxIndex);
};

#endif // DEMOWINDOW_H
