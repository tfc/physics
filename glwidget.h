#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "painterwidget.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QWidget;
QT_END_NAMESPACE

class GLWidget : public QGLWidget, public PainterWidget
{
    Q_OBJECT

public:
    GLWidget(WorldEngine *setWorld, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
};

#endif
