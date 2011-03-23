#ifndef ROPEFORCE_H
#define ROPEFORCE_H

#include "physics_engine/physicalforce.h"
class PhysicalObject;

class RopeForce : public PhysicalForce
{
public:
    RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb);

    virtual void invite(class Inviter &host) { host.visit(*this); }

    virtual Vector3 approxM(PhysicalObject *caller) const;

    PhysicalObject* getFirst() { return obA; }
    PhysicalObject* getSecond() { return obB; }
protected:
    PhysicalObject *obA;
    PhysicalObject *obB;

    double len;
    double sprConst;
    double friction;
};

#endif // ROPEFORCE_H
