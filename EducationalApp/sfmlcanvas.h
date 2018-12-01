#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include <QLabel>
#include <QTimer>

#include "SFML/Graphics.hpp"

class SfmlCanvas : public QLabel
{
    Q_OBJECT

protected:
    ///
    /// \brief imageTexture
    ///
    /// This is the SFML core. It is periodically painted to the QLabel.
    ///
    sf::RenderTexture imageTexture;

    ///
    /// \brief renderTimer
    ///
    /// Connected to renderToLabel, this keeps the QLabel up to date (visually) with the
    /// RenderTexture.
    ///
    QTimer renderTimer;

    ///
    /// \brief initialized
    ///
    /// Used for creating imageTexture after the SfmlCanvas has been initialized.
    ///
    bool initialized;

public:
    ///
    /// \brief SfmlCanvas
    /// \param parent
    /// \param framePeriod
    /// Inverse of the frequency, this is the length of time that passes before the next frame is
    /// updated.
    ///
    /// Creates an SfmlCanvas with the given parent and framePeriod.
    ///
    explicit SfmlCanvas(QWidget *parent = nullptr, int framePeriod = 20);

    virtual ~SfmlCanvas() {}


    virtual void showEvent(QShowEvent*);

    ///
    /// \brief texture
    /// \return
    ///
    /// Returns the RenderTexture core of this SfmlCanvas.
    ///
    virtual const sf::RenderTexture& texture();

    ///
    /// \brief onInit
    ///
    /// To be called as the RenderTexture is being initialized.
    ///
    virtual void onInit();

    ///
    /// \brief onUpdate
    ///
    /// Called everytime before the RenderTexture is painted to the QLabel.
    ///
    virtual void onUpdate();

signals:

public slots:
    virtual void renderToLabel();
};

#endif // SFMLCANVAS_H
