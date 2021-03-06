#include "physicalobject.h"
#include "physicalforce.h"

#include <iostream>

PhysicalObject::PhysicalObject(double _mass, double _radius, double x, double y) :
s(x, y, 0), v(0, 0, 0), a(0, 0, 0),
bs(0, 0, 0), bv(0, 0, 0), ba(0, 0, 0),
ts(x, y, 0), tv(0, 0, 0), ta(0, 0, 0),
tbs(0, 0, 0), tbv(0, 0, 0), tba(0, 0, 0),
radius(_radius), mass(_mass),
momInertia(2*_mass*_radius*_radius/5), forces()
{
}

void PhysicalObject::refreshState(double dt)
{
  Vector3 m[4];
  std::list<PhysicalForce*>::iterator it;

  setSpeed(v);
  setAngleSpeed(bv.val.z);

  for (int n=0; n < 4; n++) {
    for (it = forces.begin(); it != forces.end(); it++) {
      m[n] += (*it)->approxM(this);
    }
    setSpeed(v +m[n]*dt/2);
    setAngleSpeed((bv +Vector3(0, 0, m[n].val.dummy)*dt/2).val.z);
  }

  Vector3 mFinal = (m[0] +m[1]*2 +m[2]*2 +m[3])/6;

  ts = s +v*dt;
  tv = v +Vector3(mFinal.val.x, mFinal.val.y)*dt;

  setAngle((bs+bv*dt).val.z);
  setAngleSpeed((bv +Vector3(0, 0, mFinal.val.dummy)*dt).val.z);
}

void PhysicalObject::refreshSubStep(double dt)
{
  if (dt == 0) return;

  ts = s +v*dt;
  tv = v;
  setAngle((bs+bv*dt).val.z);
  setAngleSpeed(bv.val.z);
  activateChange();
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
