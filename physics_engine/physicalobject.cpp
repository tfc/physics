#include "physicalobject.h"
#include "physicalforce.h"

#include <iostream>

PhysicalObject::PhysicalObject(double _mass, double _radius, double x, double y) :
s(x, y, 0), bs(0, 0, 0), ts(x, y, 0), tbs(0, 0, 0), radius(_radius), mass(_mass),
momInertia(2*_mass*_radius*_radius/5), forces()
{
}

void PhysicalObject::refreshState(double dt)
{
  Vector3 m[4];
  std::list<PhysicalForce*>::iterator it;

  for (int n=0; n < 4; n++) {
    for (it = forces.begin(); it != forces.end(); it++) {
      m[n] += (*it)->approxM(this);
    }
    tv = v +m[n]*dt/2;
  }

  Vector3 mFinal = (m[0] +m[1]*2 +m[2]*2 +m[3])/6;

  ts = s +v*dt;
  tv = v +Vector3(mFinal.val.x, mFinal.val.y)*dt;

  setAngle((bs+bv*dt).val.z);
  setAngleSpeed((bv +Vector3(0, 0, mFinal.val.dummy)*dt).val.z);
}

void PhysicalObject::refreshSubStep(double dt)
{
  Vector3 _s, _v, _a, _bs, _bv, _ba;
  _s = s;
  _v = v;
  _a = a;
  _bs = bs;
  _bv = bv;
  _ba = ba;
  activateChange();
  refreshState(dt);
  s = _s;
  v = _v;
  a = _a;
  bs = _bs;
  bv = _bv;
  ba = _ba;
}

#define SWAPVEC(a, b) do {Vector3 tmp; tmp=a; a=b; b=tmp;} while(0)
void PhysicalObject::restoreState()
{
  SWAPVEC(s, ts);
  SWAPVEC(v, tv);
  SWAPVEC(a, ta);
  SWAPVEC(bs, tbs);
  SWAPVEC(bv, tbv);
  SWAPVEC(ba, tba);
}

void PhysicalObject::activateChange()
{
  SWAPVEC(s, ts);
  SWAPVEC(v, tv);
  SWAPVEC(a, ta);
  SWAPVEC(bs, tbs);
  SWAPVEC(bv, tbv);
  SWAPVEC(ba, tba);
}

void PhysicalObject::addForce(PhysicalForce* newForce)
{
  forces.push_back(newForce);
}

void PhysicalObject::removeForce(PhysicalForce* force)
{
  forces.remove(force);
}


#define PI 3.14
void PhysicalObject::setAngle(double angle)
{
  while (angle >= PI) angle -= 2*PI;
  while (angle <  PI) angle += 2*PI;
  tbs = Vector3(0, 0, angle);
}
void PhysicalObject::setAngleSpeed(double angleSpeed)
{
  tbv = Vector3(0, 0, angleSpeed);
}
void PhysicalObject::setAngleAccel(double angleAccel)
{
  tba = Vector3(0, 0, angleAccel);
}
