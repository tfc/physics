#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "painterwidget.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

class Widget : public QWidget, public PainterWidget
{
    Q_OBJECT

public:
    Widget(WorldEngine *setWorld, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
};

#endif
