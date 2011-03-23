#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include "physics_engine/worldengine.h"
#include "physics_engine/physicalobject.h"
#include "physics_engine/inviter.h"

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

class PainterWidget : public Inviter
{
public:
    PainterWidget(WorldEngine *setWorld);

    virtual void paint(QPaintEvent *event);

    virtual void visit(class PhysicalObject &guest);
    virtual void visit(class PhysicalForce &) {}

protected:
    QPainter *painter;

    int elapsed;

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;

    WorldEngine *world;
};

#endif // PAINTERWIDGET_H
