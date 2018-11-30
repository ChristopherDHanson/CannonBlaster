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

    QVector<sf::Sprite*> sprites;

public slots:
    void updateSprites();
    void spawnCannonball();
};

#endif // DEMOWINDOW_H
