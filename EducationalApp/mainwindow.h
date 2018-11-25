#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QTimer>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer spriteTimer;
    sf::Sprite* sprite;
    int spriteSwapIdx;
    std::vector<sf::Texture> textures;
    sf::Music music;

public slots:
    void updateSprite();
};

#endif // MAINWINDOW_H
