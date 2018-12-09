#include "spritemanager.h"
#include "gif.h"


SpriteManager::SpriteManager(QImage inputSpriteSheet, int numberOfFrames, int tileWidth, int tileHeight)
{
    // parse inputSpriteSheet and place sprites into output
    input = inputSpriteSheet;
    tWidth = tileWidth;
    tHeight = tileHeight;
    numFrames = numberOfFrames;
    // Make sure input image contains specified data
    if (inputSpriteSheet.width() * inputSpriteSheet.height() < tileWidth * tileHeight * numberOfFrames) {
        throw "Invalid input parameters";
    }
    parseInput();
}

QVector<QImage> SpriteManager::GetOutput() {
    return output;
}

void SpriteManager::OutputToGif(std::string filePath) {
  //create gifwriter
  GifWriter newGifFile;

  //initialize writer
  GifBegin(&newGifFile, filePath.c_str(), output[0].width(), output[0].height(), 10);

  //take each current frame and write it
  for (size_t i = 0; i < output.length(); i++)
  {
    QImage original = output[i].convertToFormat(QImage::Format_RGBA8888);
    GifWriteFrame(&newGifFile, original.bits(), output[i].width(), output[i].height(), 10, 8, false);
  }

  //complete EOF code
  GifEnd(&newGifFile);
}

void SpriteManager::parseInput() {
    int x = 0, y = 0;
    for (int counter = 0; counter < numFrames; counter++) {
        // do a copy method to add to vector
        QImage temp = input.copy(x, y, tWidth, tHeight);
        output.push_back(temp);
        x += tWidth;
        if (input.width() - x < tWidth) {
            y += tHeight;
            x = 0;
        }
    }
}
