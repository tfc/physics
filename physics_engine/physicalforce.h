#ifndef PHYSICALFORCE_H
#define PHYSICALFORCE_H

#include "invitee.h"
#include "physicalobject.h"

class PhysicalForce : public Invitee
{
public:
    PhysicalForce() {}

    virtual void invite(class Inviter &host) { host.visit(*this); }

    virtual Vector3 approxM(PhysicalObject *caller) = 0;
};

#endif // PHYSICALFORCE_H
