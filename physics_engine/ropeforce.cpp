#include "ropeforce.h"
#include <math.h>
#include <iostream>

RopeForce::RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb) :
    obA(na), obB(nb), offsetA(0, 0), offsetB(0, 0), len(len), sprConst(sprConst), friction(friction)
{
    obA->addForce(this);
    obB->addForce(this);
}

RopeForce::RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb,
              double offsetXa, double offsetYa, double offsetXb, double offsetYb) :
    obA(na), obB(nb), offsetA(offsetXa, offsetYa), offsetB(offsetXb, offsetYb),
    len(len), sprConst(sprConst), friction(friction)
{
    obA->addForce(this);
    obB->addForce(this);
}

Vector3 RopeForce::approxM(PhysicalObject *caller) const
{
    Vector3 m;

    double mass = caller->getMass();
    double inert = caller->getMomInertia();
    Vector3 myOffset = (caller == obA) ? offsetA.rotatedZ(obA->angle().val.z) : offsetB.rotatedZ(obB->angle().val.z);

    Vector3 ds = getRopeHookPosB() -getRopeHookPosA();
    Vector3 dsm = ds;
    double skalarDiff = ds.length() -len;

    // Don't push, only pull!
    if (skalarDiff <= 0) return Vector3();

    Vector3 dv = obB->tspeed()-obA->tspeed();
    Vector3 dvm = dv;

    dsm.normalize();
    dvm.normalize();

    m = dsm*((sprConst * skalarDiff) +(dv*dsm)*friction)/mass;

    // m*mass = Force at offset position
    // r x F = torque
    // torque / inert = angleAcceleration
    m.val.dummy = (myOffset ^ m*mass/inert).val.z;

    if (caller != obA) m = m*-1;

    m.val.dummy +=  -caller->angleSpeed().val.z*0.003*friction;

    return m;
}
