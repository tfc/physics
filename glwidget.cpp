#include <QtGui>
#include "glwidget.h"
#include "helper.h"


GLWidget::GLWidget(WorldEngine *world, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), PainterWidget(world)
{
    elapsed = 0;
    setFixedSize(400, 400);
    setAutoFillBackground(false);

    painter = new QPainter();
}


void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}


void GLWidget::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
    painter->setRenderHint(QPainter::Antialiasing);
    paint(event, elapsed);
    painter->end();
}

