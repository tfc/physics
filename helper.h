#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>

#include "physics_engine/worldengine.h"
#include "physics_engine/physicalobject.h"

#include "physics_engine/inviter.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QPaintEvent;
QT_END_NAMESPACE

class Helper
{
public:
    Helper(WorldEngine *setWorld);

    virtual void visit(PhysicalObject* guest);

public:
	void paint(QPainter *painter, QPaintEvent *event, double elapsed);
	
private:
	QBrush background;
	QBrush circleBrush;
	QFont textFont;
	QPen circlePen;
    QPen textPen;

    WorldEngine *world;
};

#endif
