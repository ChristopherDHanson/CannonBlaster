#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include <QWidget>
#include <QPoint>
#include <QSize>
#include <QTimer>

#include <SFML/Graphics.hpp>

///
/// \brief The SfmlCanvas class
///
/// The SfmlCanvas class is a wrapper of QWidget and sf::RenderWindow. It provides a way to
/// integrate an SFML RenderWindow into a larger Qt interface. Most of the code is taken from and/or
/// inspired by the tutorials at https://www.sfml-dev.org/tutorials/1.6/graphics-qt.php, and at
/// https://github.com/SFML/SFML/wiki/Tutorial:-Integrating-SFML-into-Qt.
///
/// This class shouldn't be used directly, but derived.
///
class SfmlCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
    using QWidget::paintEngine; // Explicitly state this to prevent warning.

private:
    ///
    /// \brief refreshTimer
    ///
    /// An SFML RenderWindow refreshes with an event handler. However, since we want the window to
    /// refresh continually (without an external event), we will improvise with a timer. That is,
    /// this timer will run continuously in the background to refresh the RenderWindow.
    ///
    /// It will be set to the framePeriod from the constructor.
    ///
    QTimer refreshTimer;

    bool initialized;

    virtual void onInit() {}

    virtual void onUpdate() {}

    virtual const QPaintEngine* paintEngine();

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    virtual void resize(const QSize& size);

public:
    ///
    /// \brief SfmlCanvas
    /// \param parent
    /// \param framePeriod Length of time, in milliseconds, of one frame. This is the inverse of the
    /// frame rate.
    ///
    ///
    explicit SfmlCanvas(QWidget *parent, const QPoint& position, const QSize& size,
                        int framePeriod = 0);

    virtual ~SfmlCanvas() {}

signals:

public slots:
};

#endif // SFMLCANVAS_H
