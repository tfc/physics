#include <QtGui>
#include "glwidget.h"
#include "widget.h"
#include "window.h"

#include "physics_engine/staticobject.h"
#include "physics_engine/ropeforce.h"
#include "physics_engine/gravitationforce.h"

#include <iostream>

#define DT 0.02

Window::Window()
: QWidget()
{
    Widget *native = new Widget(&world, this);
    GLWidget *openGL = new GLWidget(&world, this);
	QLabel *nativeLabel = new QLabel(tr("Native"));
	nativeLabel->setAlignment(Qt::AlignHCenter);
	QLabel *openGLLabel = new QLabel(tr("OpenGL"));
    openGLLabel->setAlignment(Qt::AlignHCenter);

    PhysicalObject *mass1 = world.addObject(new StaticObject(-200, -180));
    PhysicalObject *mass2;
    PhysicalObject *mass3 = world.addObject(new StaticObject(-200, -80));
    PhysicalObject *mass4;
    for (int i=1; i < 10; i++) {
        mass2 = world.addObject(new PhysicalObject(50, -200+i*40, -180));
        world.addForce(new RopeForce(10, 100, 20, mass1, mass2));
        new GravitationForce(9.81, 0, 1, 0, mass2);
        mass4 = world.addObject(new PhysicalObject(50, -200+i*40, -80));
        world.addForce(new RopeForce(10, 100, 20, mass3, mass4));
        new GravitationForce(9.81, 0, 1, 0, mass4);

        world.addForce(new RopeForce(100, 100, 20, mass2, mass4));

        mass1 = mass2;
        mass3 = mass4;
    }

    mass2 = world.addObject(new StaticObject(200, -180));
    world.addForce(new RopeForce(10, 100, 10, mass1, mass2));
    mass4 = world.addObject(new StaticObject(200, -80));
    world.addForce(new RopeForce(10, 100, 10, mass3, mass4));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(native, 0, 0);
	layout->addWidget(openGL, 0, 1);
	layout->addWidget(nativeLabel, 1, 0);
	layout->addWidget(openGLLabel, 1, 1);
	setLayout(layout);
	
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshWorld()));
    timer->start(1000*DT);
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
	connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
	timer->start(50);
	
    setWindowTitle(tr("2D Physics on Native and OpenGL Widgets"));
}

void Window::refreshWorld()
{
    //QTime timer;
    //timer.start();
    world.refreshWorld(DT);
    //int milliSecs = timer.elapsed();

    //std::cout << "Took " << milliSecs << "ms for calculations." << std::endl;
}
