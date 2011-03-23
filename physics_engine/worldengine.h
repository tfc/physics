#ifndef WORLDENGINE_H
#define WORLDENGINE_H

#include <list>

#include "physics_engine/physicalobject.h"
#include "physics_engine/physicalforce.h"

#include "physics_engine/invitee.h"

class Inviter;

#define DT 0.02 // Values bigger than 0.6 make it unstable

class WorldEngine : public Invitee
{
public:
    WorldEngine();

    virtual void invite(class Inviter &host);

    PhysicalObject* addObject(PhysicalObject *newObj);

    void refreshWorld(double dt);

private:
    std::list<PhysicalObject*> objects;
};

#endif // WORLDENGINE_H
