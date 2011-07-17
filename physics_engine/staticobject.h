#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "physicalobject.h"

class StaticObject : public PhysicalObject
{
public:
    StaticObject(double radius, double x, double y);

    virtual void refreshState(double) {}
    virtual void refreshSubStep(double dt) {}
};

#endif // STATICOBJECT_H
