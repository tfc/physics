#ifndef PHYSICALFORCE_H
#define PHYSICALFORCE_H

#include "physicalobject.h"

class PhysicalForce
{
public:
    PhysicalForce() {};

    virtual Vector3 approxM(PhysicalObject *caller) const = 0;
};

#endif // PHYSICALFORCE_H
