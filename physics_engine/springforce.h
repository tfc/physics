#ifndef SPRINGFORCE_H
#define SPRINGFORCE_H

#include "physicalforce.h"

class PhysicalObject;

class SpringForce : public PhysicalForce
{
public:
    SpringForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb);

    virtual Vector3 approxM(PhysicalObject *caller);

private:
    PhysicalObject *obA;
    PhysicalObject *obB;

    double len;
    double sprConst;
    double friction;
};

#endif // SPRINGFORCE_H
