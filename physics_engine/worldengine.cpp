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

#define RADIUSSQR 20*20
#define COLFRIC 0.9
void WorldEngine::refreshWorld(double dt)
{
  // Recalculate positions
  for (std::list<PhysicalObject*>::iterator it = objects.begin(); it != objects.end(); it++)
    (*it)->refreshState(dt);

#if 0
  // Look for collisions and handle them
  for (std::list<PhysicalObject*>::iterator outerIt = objects.begin(); outerIt != objects.end(); outerIt++) {
    std::list<PhysicalObject*>::iterator innerIt = outerIt;
    innerIt++;
    PhysicalObject *a = *outerIt;
    for (; innerIt != objects.end(); innerIt++) {
      PhysicalObject *b = *innerIt;

      double distance = (a->tposition()-b->tposition()).lengthSquare();
      if (RADIUSSQR > distance) {
        // Colliding!
        Vector3 vA = a->tspeed();
        Vector3 vB = b->tspeed();
        Vector3 vd = vA-vB;
        double mA = a->getMass();
        double mB = b->getMass();

        //vA -= vd*(1+0.9)/(1+mA/mB);
        //vB += vd*(1+0.9)/(1+mB/mA);
        vA = (a->tspeed() *(mA -COLFRIC*mB) +b->tspeed()*(COLFRIC+1)*mB)/(mA+mB);
        vB = (a->tspeed()*(COLFRIC+1)*mA +b->tspeed()*(mB -COLFRIC*mA))/(mA+mB);

        a->setSpeed(vA);
        b->setSpeed(vB);
      }
    }
  }
#endif

  // Apply new states
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
