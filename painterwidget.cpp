/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "painterwidget.h"

#include "physics_engine/ropeforce.h"

#include <iostream>

PainterWidget::PainterWidget(WorldEngine *setWorld)
    : world(setWorld)
{
    QLinearGradient backGradient(0, 0, 0, 400);
    backGradient.setColorAt(1.0, Qt::white);
    backGradient.setColorAt(0.0, QColor(180, 200, 255));
    background = QBrush(backGradient);

    QRadialGradient gradient(-5, -5, 10);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0, 0, 0));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);

    textPen = QPen(Qt::gray);
    textFont.setPixelSize(50);

}

void PainterWidget::paint(QPaintEvent *event)
{
    painter->fillRect(event->rect(), background);
    painter->translate(0, 0);

    world->invite(*this);

    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(700, 500, 100, 100), Qt::AlignCenter, "Qt");
}

void PainterWidget::visit(class PhysicalObject &guest)
{
    Vector3 pos = guest.position()*100;

    painter->save();
    painter->translate(pos.x(), pos.y());
    painter->rotate(guest.angle().val.z/3.14*180);
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    qreal circleRadius = guest.getRadius()*100;
    painter->drawEllipse(QRectF(-circleRadius, -circleRadius, circleRadius*2, circleRadius*2));

    painter->restore();
}

void PainterWidget::visit(class RopeForce &guest)
{
    QPen pen(Qt::darkGreen, 3, Qt::SolidLine);

    Vector3 pos1 = guest.getRopeHookPosA()*100;
    Vector3 pos2 = (guest.getRopeHookPosB() -pos1/100)*100;

    painter->save();
    painter->setPen(pen);
    painter->translate(pos1.x(), pos1.y());

    painter->drawLine(QPointF(0, 0), QPointF(pos2.x(), pos2.y()));

    painter->restore();
}
