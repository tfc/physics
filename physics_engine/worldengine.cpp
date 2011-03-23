#include "physics_engine/worldengine.h"

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

void WorldEngine::refreshWorld(double dt)
{
    for (std::list<PhysicalObject*>::iterator it = objects.begin(); it != objects.end(); it++)
        (*it)->refreshState(dt);
    for (std::list<PhysicalObject*>::iterator it = objects.begin(); it != objects.end(); it++)
        (*it)->activateChange();
}

void WorldEngine::invite(Inviter *host)
{
    for (std::list<PhysicalObject*>::iterator it = objects.begin();
    it != objects.end();
    ++it)
    {
        (*it)->invite(host);
    }
}