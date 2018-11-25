#ifndef CANVAS_H
#define CANVAS_H

#include "sfmlcanvas.h"

///
/// \brief The Canvas class
///
/// Canvas is an implementation/derivation of SfmlCanvas that allows for
class Canvas : public SfmlCanvas
{
private:
    std::vector<sf::Sprite*> sprites;

    void onInit() override;

    void onUpdate() override;

public:
    Canvas(QWidget* parent, const QPoint& position = QPoint(0, 0), const QSize& size = QSize(0, 0));

    ~Canvas() override;

    void addSprite(sf::Sprite* sprite);

    void removeSprite(sf::Sprite* sprite);
};

#endif // CANVAS_H
