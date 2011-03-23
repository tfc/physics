#include "physics_engine/physicalobject.h"
#include "physics_engine/physicalforce.h"

PhysicalObject::PhysicalObject(double _mass, double x, double y) :
    s(x, y, 0), ts(x, y, 0), mass(_mass), forces()
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
    tv = v +mFinal*dt;

}

void PhysicalObject::activateChange()
{
    s = ts;
    v = tv;
    a = ta;
}

void PhysicalObject::addForce(PhysicalForce* newForce)
{
    forces.push_back(newForce);
}

void PhysicalObject::removeForce(PhysicalForce* force)
{
    forces.remove(force);
}
