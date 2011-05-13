#include "worldengine.h"

#include <QTime>
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

#define ITOL 8
void WorldEngine::refreshWorld(double dt)
{
  std::list<PhysicalObject*>::iterator it;
  std::list<PhysicalObject*>::iterator it2;

  // Recalculate positions
  for (it = objects.begin(); it != objects.end(); it++)
    (*it)->refreshState(dt);

  // Apply new states
  for (it = objects.begin(); it != objects.end(); it++)
    (*it)->activateChange();

  for (it = objects.begin(); it != objects.end(); it++) {
    for (it2 = it, it2++; it2 != objects.end(); it2++) {
      PhysicalObject *a = *it;
      PhysicalObject *b = *it2;
      int tryAgain = 0;
      unsigned int i = 0;
      double curdt = dt;

      if (collisionOccured(*a, *b) == 0) continue;
      do {
        ++i;
        switch (collisionOccured(*a, *b)) {
        case -1: // Overlap
          tryAgain = 1;
          curdt -= dt/(1 << i);
          a->restoreState();
          b->restoreState();
          a->refreshState(curdt);
          b->refreshState(curdt);
          break;
        case 0: // Not colliding yet
          tryAgain = 1;
          curdt += dt/(1 << i);
          a->restoreState();
          b->restoreState();
          a->refreshState(curdt);
          b->refreshState(curdt);
          break;
        case 1: // Normal collision
          tryAgain=0;
        }
      } while (tryAgain && i < ITOL);
      applyImpulse(*a, *b);
      a->refreshSubStep(dt-curdt);
      b->refreshSubStep(dt-curdt);
      a->activateChange();
      b->activateChange();
    }
  }
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

  if ((fabs(s) <= COL_TOLERANCE) && (vRelNorm < 0.0))
    return 1; // Normal collision
  else if (s < -COL_TOLERANCE)
    return -1; // overlapping

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
