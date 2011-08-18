#include "ropeforce.h"
#include <math.h>
#include <iostream>

RopeForce::RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb) :
    obA(na), obB(nb), offsetA(0, 0), offsetB(0, 0), len(len), sprConst(sprConst), friction(friction), cached(false)
{
    obA->addForce(this);
    obB->addForce(this);
}

RopeForce::RopeForce(double len, double sprConst, double friction, PhysicalObject* na, PhysicalObject* nb,
              double offsetXa, double offsetYa, double offsetXb, double offsetYb) :
    obA(na), obB(nb), offsetA(offsetXa, offsetYa), offsetB(offsetXb, offsetYb),
    len(len), sprConst(sprConst), friction(friction), cached(false)
{
    obA->addForce(this);
    obB->addForce(this);
}

Vector3 RopeForce::approxM(PhysicalObject *caller)
{
  /* Generic part BEGIN */
    if (!cached) {
      Vector3 ds = getRopeHookPosB() -getRopeHookPosA();
      Vector3 dsm = ds;
      double skalarDiff = ds.length() -len;

      // Don't push, only pull!
      if (skalarDiff <= 0) {
        noPull = cached = true;
        return Vector3();
      }

      Vector3 dv = obB->tspeed()-obA->tspeed();
      Vector3 dvm = dv;

      dsm.normalize();
      dvm.normalize();

      m = dsm *sprConst *skalarDiff; // Rope force
      if (dvm*dsm > 0) m += dsm *(dv *dsm) *friction; // Friction in PULL-direction
      m += dsm.perpendicular() *(dv *dsm.perpendicular()) *friction *0.01; // Friction against shaking
    }

    if (noPull) {
      cached = noPull = false;
      return Vector3();
    }

  /* Generic part END */

  /* A/B specific part BEGIN */
    Vector3 ret;
    double mass = caller->getMass();
    double inert = caller->getMomInertia();
    Vector3 myOffset = (caller == obA) ? offsetA.rotatedZ(obA->angle().val.z) : offsetB.rotatedZ(obB->angle().val.z);
    ret = m/mass;

    // m*mass = Force at offset position
    // r x F = torque
    // torque / inert = angleAcceleration
    ret.val.dummy = (myOffset ^ m/inert).val.z;

    if (caller != obA) ret = ret*-1;

    ret.val.dummy +=  -caller->tangleSpeed().val.z*0.03*friction;

  /* A/B specific part END */

    if (!cached) cached = true;
    else cached = noPull = false;

    return ret;
}
