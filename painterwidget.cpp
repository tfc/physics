#include "painterwidget.h"

#include <iostream>

PainterWidget::PainterWidget(WorldEngine *setWorld)
    : elapsed(0), world(setWorld)
{
    QRadialGradient gradient(-5, -5, 10);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(255, 0, 0));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void PainterWidget::paint(QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    painter->translate(200, 200);

    world->invite(*this);

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, "Qt");
}

void PainterWidget::visit(class PhysicalObject &guest)
{
    Vector3 pos = guest.position();

    painter->save();
    painter->translate(pos.x(), pos.y());
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    qreal circleRadius = 10;
    painter->drawEllipse(QRectF(-circleRadius, -circleRadius, circleRadius*2, circleRadius*2));

    painter->restore();
}
