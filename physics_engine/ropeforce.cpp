#include "physics_engine/ropeforce.h"
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
    double skalarDiff = ds.length() -len;

    // Don't push, only pull!
    if (skalarDiff <= 0) return Vector3();

    Vector3 dv = obB->tspeed()-obA->tspeed();

    double angle = ds.angle();

    m.val.x = (sprConst *skalarDiff *cos(angle) +friction*dv.val.x)/mass;
    m.val.y = (sprConst *skalarDiff *sin(angle) +friction*dv.val.y)/mass;
    m.val.dummy = sprConst*(myOffset.val.x *skalarDiff*sin(angle) -myOffset.val.y*skalarDiff*cos(angle))/inert;

    if (caller != obA) m = m*-1;

    m.val.dummy -= friction*0.1*caller->angleSpeed().val.z;

    return m;
}
