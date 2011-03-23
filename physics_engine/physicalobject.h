#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include <list>

#include "physics_engine/invitee.h"
#include "physics_engine/Vector3.h"

class PhysicalForce;

class PhysicalObject : public Invitee
{
public:
    PhysicalObject(double _mass, double x, double y);

    virtual void refreshState(double dt);
    virtual void activateChange();

    virtual void invite(class Inviter &host) { host.visit(*this); }

    void addForce(PhysicalForce* newForce);
    void removeForce(PhysicalForce* force);

    Vector3 position() const { return s; }
    Vector3 speed() const { return v; }
    Vector3 accel() const { return a; }
    Vector3 tposition() const { return ts; }
    Vector3 tspeed() const { return tv; }
    Vector3 taccel() const { return ta; }
    double getMass() const { return mass; }

protected:
    void setPosition(double x, double y) {ts.val.x = x; ts.val.y=y;}
    void setSpeed(double x, double y) {tv.val.x = x; tv.val.y=y;}
    void setAccel(double x, double y) {ta.val.x = x; ta.val.y=y;}
    void setPosition(Vector3 newPos) {ts = newPos;}
    void setSpeed(Vector3 newSpeed) {tv = newSpeed;}
    void setAccel(Vector3 newAccel) {ta = newAccel;}

private:
    Vector3 s;
    Vector3 v;
    Vector3 a;

    // Temp values
    Vector3 ts;
    Vector3 tv;
    Vector3 ta;

    double mass;

    std::list<PhysicalForce*> forces;
};

#endif // PHYSICALOBJECT_H
