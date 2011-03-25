#include "physicalobject.h"
#include "physicalforce.h"

#include <iostream>

PhysicalObject::PhysicalObject(double _mass, double x, double y) :
    s(x, y, 0), bs(0, 0, 0), ts(x, y, 0), tbs(0, 0, 0), mass(_mass), momInertia(2*_mass*10*10/5), forces()
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

    tbs = bs +bv*dt;
    tbv = bv +Vector3(0, 0, mFinal.val.dummy)*dt;
}

void PhysicalObject::activateChange()
{
    s = ts;
    v = tv;
    a = ta;
    bs = tbs;
    bv = tbv;
    ba = tba;
}

void PhysicalObject::addForce(PhysicalForce* newForce)
{
    forces.push_back(newForce);
}

void PhysicalObject::removeForce(PhysicalForce* force)
{
    forces.remove(force);
}
