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
        world.addForce(new RopeForce(10, 100, 20, mass1, mass2, 10, 0, -10, 0));
        new GravitationForce(9.81, 0, 1, 0, mass2);
        mass4 = world.addObject(new PhysicalObject(50, -200+i*40, -80));
        world.addForce(new RopeForce(10, 100, 20, mass3, mass4, 10, 0, -10, 0));
        new GravitationForce(9.81, 0, 1, 0, mass4);

        world.addForce(new RopeForce(100, 100, 20, mass2, mass4, 0, 10, 0, -10));

        mass1 = mass2;
        mass3 = mass4;
    }

    mass2 = world.addObject(new StaticObject(200, -180));
    world.addForce(new RopeForce(10, 100, 10, mass1, mass2, 10, 0, -10, 0));
    mass4 = world.addObject(new StaticObject(200, -80));
    world.addForce(new RopeForce(10, 100, 10, mass3, mass4, 10, 0, -10, 0));

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
    timer->start(40);
	
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
