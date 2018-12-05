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
    sf::Music music;
    QVector<Level*> levels;
    Level* currentLevel;
    QVector<sf::Sprite*> sprites;
    float angle[2];
    float velocity;
    float density;

public slots:
    void updateSprites();
    void spawnCannonball();
    void changeVelocity();
    void changeAngle();
    void changeDensity();
};

#endif // DEMOWINDOW_H
