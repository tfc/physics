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

#define ITOL 10
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
      double curdt = dt;

      switch (collisionOccured(*a, *b)) {
      case 0:
        continue;
      case -1:
        // Resolve contact before overlap
        a->restoreState();
        b->restoreState();
        curdt = rewindOverlap(*a, *b);
        a->refreshState(curdt);
        b->refreshState(curdt);
      }
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

#define COL_TOLERANCE (0.0000001)
int WorldEngine::collisionOccured(const PhysicalObject &obA, const PhysicalObject &obB)
{
  Vector3 d;
  Vector3 v1, v2;
  double r; // radius of both centers
  double s; // distance of centers -radius of centers
  double vRelNorm;

  r = obA.getRadius() +obB.getRadius();
  d = obA.position() -obB.position();
  s = d.length() -r;

  d.normalize();
  v1 = obA.speed();
  v2 = obB.speed();

  // Relative speed (normalized)
  // = skalar product between relSpeed and normalized distance vector
  vRelNorm = (v1 -v2) *d;

  if ((fabs(s) <= COL_TOLERANCE) && (vRelNorm < 0.00000001))
    return 1; // Normal collision
  else if (s < -COL_TOLERANCE)
    return -1; // overlapping

  return 0;
}

double WorldEngine::rewindOverlap(PhysicalObject &obA, PhysicalObject &obB)
{
  double t;

  t = ((obB.position()-obA.position()).length() -(obA.getRadius()+obB.getRadius()))/(obB.speed()-obA.speed()).length();

  return t;
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
