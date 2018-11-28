#include "canvas.h"

Canvas::Canvas(QWidget* parent) : SfmlCanvas(parent), sprites()
{ }

void Canvas::addSprite(sf::Sprite* sprite)
{
    sprites.push_back(sprite);
}

void Canvas::removeSprite(sf::Sprite* sprite)
{
    int found = 0;

    for (uint16_t idx = 0; idx < sprites.size(); idx++)
        if (sprites[idx] == sprite)
            for (uint16_t idx2 = idx + 1; idx2 < sprites.size(); idx2++)
            {
                sprites[idx2 - 1] = sprites[idx2];
                found++;
            }

    while (found-- > 0)
        sprites.pop_back();
}

void Canvas::renderToLabel()
{
    paintTexture();
    sf::Image sfImage = imageTexture.getTexture().copyToImage();

    // Somehow, the image normally comes upside down. So we flip it.
    sfImage.flipVertically();

    const uint8_t* pixelMap = sfImage.getPixelsPtr();
    QSize widgetSize = size();
    QImage image(pixelMap, widgetSize.width(), widgetSize.height(), QImage::Format_ARGB32);

    image = image.rgbSwapped();

    setPixmap(QPixmap::fromImage(image));
}

void Canvas::paintTexture()
{
    // Paint the background black. Paint it black!
    imageTexture.clear(sf::Color(0, 0, 0, 255));

    for (sf::Sprite* spritePtr : sprites)
        imageTexture.draw(*spritePtr);
}
