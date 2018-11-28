#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include <QLabel>
#include <QTimer>

#include "SFML/Graphics.hpp"

class SfmlCanvas : public QLabel
{
    Q_OBJECT

protected:
    sf::RenderTexture imageTexture;
    QTimer renderTimer;
    bool initialized;

public:
    explicit SfmlCanvas(QWidget *parent = nullptr, int framePeriod = 1);

    virtual void showEvent(QShowEvent*);

    virtual const sf::RenderTexture& texture();

    virtual void onInit();

signals:

public slots:
    virtual void renderToLabel();
};

#endif // SFMLCANVAS_H
