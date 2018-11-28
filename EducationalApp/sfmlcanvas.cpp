#include "SfmlCanvas.h"

SfmlCanvas::SfmlCanvas(QWidget *parent, int framePeriod) : QLabel(parent), initialized(false)
{
    // Apparently this allows the widget to receive key events.
    QWidget::setFocusPolicy(Qt::StrongFocus);

    // Setup the refreshTimer for refreshing the frame
    renderTimer.setInterval(framePeriod);
}

void SfmlCanvas::showEvent(QShowEvent*)
{
    if (!initialized)
    {
        QSize widgetSize = QWidget::size();
        imageTexture.create(static_cast<unsigned int>(widgetSize.width()),
                     static_cast<unsigned int>(widgetSize.height()));

        imageTexture.setSmooth(true);

        // Let the derived class do its specific stuff
        onInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&renderTimer, &QTimer::timeout, this, &SfmlCanvas::renderToLabel);
        renderTimer.start();

        initialized = true;
    }
}

const sf::RenderTexture& SfmlCanvas::texture()
{
    return imageTexture;
}

void SfmlCanvas::onInit()
{ }

void SfmlCanvas::renderToLabel()
{
    // Transform the RenderTexture object into something that Qt can recognize.
    const uint8_t* pixelMap = imageTexture.getTexture().copyToImage().getPixelsPtr();
    QSize widgetSize = size();
    QImage image(pixelMap, widgetSize.width(), widgetSize.height(), QImage::Format_ARGB32);

    image = image.rgbSwapped();

    setPixmap(QPixmap::fromImage(image));
}
