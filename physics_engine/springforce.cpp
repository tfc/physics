#include "springforce.h"
#include <math.h>
#include <iostream>

SpringForce::SpringForce(double len, double sprConst, double fric, PhysicalObject* na, PhysicalObject* nb) :
    obA(na), obB(nb), len(len), sprConst(sprConst), friction(fric)
{
    obA->addForce(this);
    obB->addForce(this);
}

Vector3 SpringForce::approxM(PhysicalObject *caller) const
{
    Vector3 m;

    double mass = caller->getMass();

    Vector3 ds = obB->tposition()-obA->tposition();
    Vector3 dv = obB->tspeed()-obA->tspeed();

    double angle = ds.angle();
    ds *= 1-len/ds.length();

    double skalarDiff = ds.length() -len;

    m.val.x = (sprConst * skalarDiff *cos(angle) +friction*dv.val.x)/mass;
    m.val.y = (sprConst * skalarDiff *sin(angle) +friction*dv.val.y)/mass;

    if (caller != obA) m = m*-1;
    return m;
}
