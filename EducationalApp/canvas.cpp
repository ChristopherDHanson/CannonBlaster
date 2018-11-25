#include "canvas.h"

Canvas::Canvas(QWidget* parent, const QPoint& position, const QSize& size) :
    SfmlCanvas(parent, position, size)
{ }


Canvas::~Canvas()
{
//    for (uint16_t idx = 0; idx < sprites.size(); idx++)
//        if (sprites[idx])
//            delete sprites[idx];
}

void Canvas::onInit()
{ }

void Canvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color(0, 0, 0));

    for (sf::Sprite* spritePtr : sprites)
        sf::RenderWindow::draw(*spritePtr);
}

void Canvas::addSprite(sf::Sprite* sprite)
{
    sprites.push_back(sprite);
}

void Canvas::removeSprite(sf::Sprite* sprite)
{
    sf::Sprite* spritePtr;
    int removed = 0;

    for (uint16_t idx = 0; idx < sprites.size(); idx++)
    {
        spritePtr = sprites[idx];
        if (sprite == spritePtr)
        {
            for (uint16_t j = idx + 1; j < sprites.size(); j++)
                sprites[j - 1] = sprites[j];
            ++removed;
        }
    }

    while (removed-- > 0)
        sprites.pop_back();
}
