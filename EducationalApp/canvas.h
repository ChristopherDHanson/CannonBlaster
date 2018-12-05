#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <iostream>
#include <Box2D/Box2D.h>
#include <QLabel>

#include "sfmlcanvas.h"

class Canvas : public SfmlCanvas
{
    Q_OBJECT

private:
    ///
    /// \brief sprites
    ///
    /// A vector of sprites that will be painted to the Canvas every frame.
    ///
    std::vector<sf::Sprite*> sprites;

    sf::Texture backdropTexture;

    ///
    /// \brief backdrop
    ///
    /// Background texture of the canvas. This doesn't move, and it should cover the whole image.
    ///
    sf::Sprite backdrop;

    ///
    /// \brief paintSprites
    ///
    /// Helper method for painting all the sprites in the Canvas.
    ///
    void paintSprites();

    ///
    /// \brief paintBackdrop
    ///
    /// Paints the backdrop to the imageTexture. This should be called from onUpdate.
    ///
    void paintBackdrop();

public:
    ///
    /// \brief Canvas
    /// \param parent
    ///
    /// Creates a new Canvas with the given parent.
    ///
    Canvas(QWidget* parent = nullptr);

    ~Canvas() override;

    ///
    /// \brief addSprite
    /// \param sprite
    ///
    /// Puts another sprite on the Canvas.
    ///
    void addSprite(sf::Sprite* sprite);

    void removeSprite(sf::Sprite* sprite);

    void onUpdate() override;

    void setBackdrop(std::string backdropPath);

public slots:
};

#endif // CANVAS_H
