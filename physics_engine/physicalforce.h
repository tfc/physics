#ifndef PHYSICALFORCE_H
#define PHYSICALFORCE_H

#include "physics_engine/invitee.h"
#include "physics_engine/physicalobject.h"

class PhysicalForce : public Invitee
{
public:
    PhysicalForce() {}

    virtual void invite(class Inviter &host) { host.visit(*this); }

    virtual Vector3 approxM(PhysicalObject *caller) const = 0;
};

#endif // PHYSICALFORCE_H
