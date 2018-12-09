#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <QImage>
#include <iostream>

class SpriteManager
{
private:
    QImage input;
    QVector<QImage> output;
    int tWidth;
    int tHeight;
    int numFrames;
    void parseInput();
public:
    SpriteManager(QImage inputSpriteSheet, int numberOFFrames, int tileWidth, int tileHeight);
    QVector<QImage> GetOutput();
    void OutputToGif(std::string filePath);
};

#endif // SPRITEMANAGER_H
