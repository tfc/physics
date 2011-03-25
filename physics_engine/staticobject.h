#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "physicalobject.h"

class StaticObject : public PhysicalObject
{
public:
    StaticObject(double x, double y);

    virtual void refreshState(double) {}
};

#endif // STATICOBJECT_H
