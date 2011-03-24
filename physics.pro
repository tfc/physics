QT     += opengl

TARGET  = physics
TEMPLATE = app

HEADERS = \
    painterwidget.h \
    glwidget.h \
    widget.h \
    window.h \
    physics_engine/Vector3.h \
    physics_engine/springforce.h \
    physics_engine/physicalobject.h \
    physics_engine/physicalforce.h \
    physics_engine/gravitationforce.h \
    physics_engine/ropeforce.h \
    physics_engine/worldengine.h \
    physics_engine/inviter.h \
    physics_engine/invitee.h \
    physics_engine/staticobject.h
SOURCES = \
    painterwidget.cpp \
    glwidget.cpp \
    main.cpp \
    widget.cpp \
    window.cpp \
    physics_engine/Vector3.cpp \
    physics_engine/springforce.cpp \
    physics_engine/physicalobject.cpp \
    physics_engine/gravitationforce.cpp \
    physics_engine/ropeforce.cpp \
    physics_engine/worldengine.cpp \
    physics_engine/inviter.cpp \
    physics_engine/invitee.cpp \
    physics_engine/staticobject.cpp

OTHER_FILES += \
    README
