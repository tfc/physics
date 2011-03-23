#ifndef ROPEFORCE_H
#define ROPEFORCE_H

#include "physicalforce.h"
class PhysicalObject;

class RopeForce : public PhysicalForce
{
public:
    RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb);

    virtual Vector3 approxM(PhysicalObject *caller) const;

protected:
    PhysicalObject *obA;
    PhysicalObject *obB;

    double len;
    double sprConst;
    double friction;
};

#endif // ROPEFORCE_H
