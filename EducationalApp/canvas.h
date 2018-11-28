#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

#include <QLabel>

#include "sfmlcanvas.h"

class Canvas : public SfmlCanvas
{
    Q_OBJECT

private:
    std::vector<sf::Sprite*> sprites;

    void paintTexture();

    public:
    Canvas(QWidget* parent = nullptr);

    void addSprite(sf::Sprite* sprite);

    void removeSprite(sf::Sprite* sprite);

public slots:
    void renderToLabel() override;
};

#endif // CANVAS_H
