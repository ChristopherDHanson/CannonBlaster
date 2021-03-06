
#include "canvas.h"

Canvas::Canvas(QWidget* parent) : SfmlCanvas(parent), sprites(), backdropTexture(), backdrop()
{ }

Canvas::~Canvas()
{
    // It is not the responsibility of the Canvas to destroy the sprites. If you want to change
    // that, it's fine, but make that clear with commenting.
}

void Canvas::addSprite(sf::Sprite* sprite)
{
    sprites.push_back(sprite);
}

void Canvas::removeSprite(sf::Sprite* sprite)
{
    int found = 0;

    for (uint16_t idx = 0; idx < sprites.size(); idx++)
        if (sprites[idx] == sprite) {
            for (uint16_t idx2 = idx + 1; idx2 < sprites.size(); idx2++)
                sprites[idx2 - 1] = sprites[idx2];
            found++;
        }

    while (found-- > 0)
        sprites.pop_back();
}

void Canvas::removeSprites(std::vector<uint16_t> indices)
{
    int found = 0;

    for (uint16_t idx : indices) {
        for (uint16_t idx2 = idx + 1; idx2 < sprites.size(); idx2++)
            sprites[idx2 - 1] = sprites[idx2];
        found++;
    }
//    for (uint16_t idx = 0; idx < sprites.size(); idx++)
//        if (sprites[idx] == sprite) {
//            for (uint16_t idx2 = idx + 1; idx2 < sprites.size(); idx2++)
//                sprites[idx2 - 1] = sprites[idx2];
//            found++;
//        }

    while (found-- > 0)
        sprites.pop_back();
}

void Canvas::removeAllSprites()
{
    sprites.clear();
}

uint16_t Canvas::spriteCnt()
{
    return static_cast<uint16_t>(sprites.size());
}

void Canvas::onUpdate()
{
    paintBackdrop();
    paintSprites();
}

void Canvas::paintSprites()
{
    for (sf::Sprite* spritePtr : sprites) {
        imageTexture.draw(*spritePtr);
        //std::cout << spritePtr->getOrigin().x << " " << spritePtr->getOrigin().y << "\n";
    }
}

void Canvas::setBackdrop(std::string backdropPath)
{
    backdropTexture.loadFromFile(backdropPath);
    backdrop.setTexture(backdropTexture);
    sf::FloatRect bounds = backdrop.getGlobalBounds();
    backdrop.scale(this->width() / bounds.width, this->height() / bounds.height);
}

void Canvas::paintBackdrop()
{
    imageTexture.draw(backdrop);
}
