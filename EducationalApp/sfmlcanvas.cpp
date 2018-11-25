#include <iostream>

#include <QWidget>

//#include <SFML/Graphics.hpp>

#include "sfmlcanvas.h"

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

SfmlCanvas::SfmlCanvas(QWidget *parent, const QPoint& position, const QSize& size,
                       int framePeriod) : QWidget(parent), sf::RenderWindow(), initialized(false)
{
    // Setup some states to allow direct rendering into the widget
    QWidget::setAttribute(Qt::WA_PaintOnScreen);
    QWidget::setAttribute(Qt::WA_OpaquePaintEvent);
    QWidget::setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    QWidget::setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    QWidget::move(position);
    QWidget::resize(size);

    // Setup the refreshTimer for refreshing the frame
    refreshTimer.setInterval(framePeriod);
}

void SfmlCanvas::showEvent(QShowEvent*)
{
    if (!initialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        sf::RenderWindow::create(static_cast<sf::WindowHandle>(QWidget::winId()));

        // Let the derived class do its specific stuff
        onInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        refreshTimer.start();

        initialized = true;
    }
}

const QPaintEngine* SfmlCanvas::paintEngine()
{
    return nullptr;
}

void SfmlCanvas::paintEvent(QPaintEvent*)
{
    // Let the derived class do its specific stuff
    onUpdate();

    // Display on screen
    display();
}

void SfmlCanvas::resize(const QSize& size)
{
    QWidget::resize(size);
    std::cout << "SFML Canvas resize" << std::endl;
    sf::RenderWindow::create(static_cast<sf::WindowHandle>(QWidget::winId()));
}
