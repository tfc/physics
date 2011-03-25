#ifndef ROPEFORCE_H
#define ROPEFORCE_H

#include "physicalforce.h"

class PhysicalObject;

class RopeForce : public PhysicalForce
{
public:
    RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb);
    RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb,
              double offsetXa, double offsetYa, double offsetXb, double offsetYb);

    virtual void invite(class Inviter &host) { host.visit(*this); }

    virtual Vector3 approxM(PhysicalObject *caller) const;

    PhysicalObject* getObjA() { return obA; }
    PhysicalObject* getObjB() { return obB; }
    Vector3 getOffsetA() const { return offsetA; }
    Vector3 getOffsetB() const { return offsetB; }

    Vector3 getRopeHookPosA() const
    { return obA->position()+(offsetA.rotatedZ(obA->angle().val.z)); }
    Vector3 getRopeHookPosB() const
    { return obB->position()+(offsetB.rotatedZ(obB->angle().val.z)); }

protected:
    PhysicalObject *obA;
    PhysicalObject *obB;

    Vector3 offsetA;
    Vector3 offsetB;

    double len;
    double sprConst;
    double friction;
};

#endif // ROPEFORCE_H
