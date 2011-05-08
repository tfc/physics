#ifndef WORLDENGINE_H
#define WORLDENGINE_H

#include <list>

#include "physicalobject.h"
#include "physicalforce.h"

#include "invitee.h"

class Inviter;


class WorldEngine : public Invitee
{
public:
    WorldEngine();

    virtual void invite(class Inviter &host);

    PhysicalObject* addObject(PhysicalObject *newObj);
    PhysicalForce* addForce(PhysicalForce *newForce);

    void refreshWorld(double dt);

protected:
    int collisionOccured(const PhysicalObject &obA, const PhysicalObject &obB);
    void applyImpulse(PhysicalObject &obA, PhysicalObject &obB);

private:
    std::list<PhysicalObject*> objects;
    std::list<PhysicalForce*> forces;
};

#endif // WORLDENGINE_H
