#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>

#include "physicalobject.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QPaintEvent;
QT_END_NAMESPACE

class Helper
{
public:
	Helper();
	
public:
	void paint(QPainter *painter, QPaintEvent *event, double elapsed);
	void recalculate();
	
private:
	QBrush background;
	QBrush circleBrush;
	QFont textFont;
	QPen circlePen;
	QPen textPen;
};

#endif
