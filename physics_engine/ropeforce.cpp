#include "physics_engine/ropeforce.h"
#include <math.h>
#include <iostream>

RopeForce::RopeForce(double len, double sprConst, double fric, PhysicalObject* na, PhysicalObject* nb) :
    obA(na), obB(nb), len(len), sprConst(sprConst), friction(fric)
{
    obA->addForce(this);
    obB->addForce(this);
}

Vector3 RopeForce::approxM(PhysicalObject *caller) const
{
    Vector3 m;

    double mass = caller->getMass();

    Vector3 ds = obB->tposition()-obA->tposition();
    double skalarDiff = ds.length() -len;

    // Don't push, only pull!
    if (skalarDiff <= 0) return Vector3();

    Vector3 dv = obB->tspeed()-obA->tspeed();

    double angle = ds.angle();

    m.val.x = (sprConst * skalarDiff *cos(angle) +friction*dv.val.x)/mass;
    m.val.y = (sprConst * skalarDiff *sin(angle) +friction*dv.val.y)/mass;

    if (caller != obA) m = m*-1;
    return m;
}
