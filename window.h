#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "helper.h"
#include "physics_engine/worldengine.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QWidget;
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

public slots:
    void refreshWorld();

private:
    WorldEngine world;
};

#endif
