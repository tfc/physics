#include "worldengine.h"

WorldEngine::WorldEngine()
{
}

PhysicalObject* WorldEngine::addObject(PhysicalObject *newObj)
{
    objects.push_back(newObj);

    // Sort and remove duplicates
    objects.sort();
    objects.unique();

    return newObj;
}

PhysicalForce* WorldEngine::addForce(PhysicalForce *newForce)
{
    forces.push_back(newForce);

    // Sort and remove duplicates
    forces.sort();
    forces.unique();

    return newForce;
}


void WorldEngine::refreshWorld(double dt)
{
    for (std::list<PhysicalObject*>::iterator it = objects.begin(); it != objects.end(); it++)
        (*it)->refreshState(dt);
    for (std::list<PhysicalObject*>::iterator it = objects.begin(); it != objects.end(); it++)
        (*it)->activateChange();
}

void WorldEngine::invite(class Inviter &host)
{
    for (std::list<PhysicalForce*>::iterator it = forces.begin(); it != forces.end(); ++it)
        (*it)->invite(host);
    for (std::list<PhysicalObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
        (*it)->invite(host);
}
