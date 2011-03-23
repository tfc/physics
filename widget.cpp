#include <QtGui>
#include "widget.h"


Widget::Widget(WorldEngine *world, QWidget *parent)
    : QWidget(parent), PainterWidget(world)
{
    setFixedSize(400, 400);

    painter = new QPainter();
}

void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
    painter->setRenderHint(QPainter::Antialiasing);
    paint(event);
    painter->end();
}
