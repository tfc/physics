#include "worldengine.h"

#include <math.h>

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

  // Look for collisions and handle them
  for (std::list<PhysicalObject*>::iterator outerIt = objects.begin(); outerIt != objects.end(); outerIt++) {
    std::list<PhysicalObject*>::iterator innerIt = outerIt;
    innerIt++;
    PhysicalObject *a = *outerIt;
    for (; innerIt != objects.end(); innerIt++) {
      PhysicalObject *b = *innerIt;

      if (collisionOccured(*a, *b)) {
        // Colliding!
        applyImpulse(*a, *b);
      }
    }
  }

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

#define COL_TOLERANCE 0.5
int WorldEngine::collisionOccured(const PhysicalObject &obA, const PhysicalObject &obB)
{
  Vector3 d;
  Vector3 v1, v2;
  double r; // radius of both centers
  double s; // distance of centers -radius of centers
  double vRelNorm;

  r = (obA.getRadius() +obB.getRadius());
  d = obA.position() -obB.position();
  s = d.length() -r;

  d.normalize();
  v1 = obA.speed();
  v2 = obB.speed();

  // Relative speed (normalized)
  // = skalar product between relSpeed and normalized distance vector
  vRelNorm = (v1 -v2) *d;

  if ((fabs(s) <= COL_TOLERANCE) && (vRelNorm < 0.0)) {
    return 1;
  }
  else if (s < -COL_TOLERANCE) {
    return -1;
  }

  return 0;
}

#define COL_RESTITUTION 0.7
void WorldEngine::applyImpulse(PhysicalObject &obA, PhysicalObject &obB)
{
  double j;
  Vector3 colNormal = obA.position()-obB.position();
  colNormal.normalize();
  Vector3 relVelocity = obA.speed()-obB.speed();

  j = ( -(1+COL_RESTITUTION) * (relVelocity * colNormal))
      / ((colNormal*colNormal)
         * (1/obA.getMass() + 1/obB.getMass()));

  obA.setSpeed(obA.speed() +(colNormal*j)/obA.getMass());
  obB.setSpeed(obB.speed() -(colNormal*j)/obB.getMass());
}
