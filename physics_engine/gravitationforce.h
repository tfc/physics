#ifndef GRAVITATIONFORCE_H
#define GRAVITATIONFORCE_H

#include "physicalforce.h"

class PhysicalObject;

class GravitationForce : public PhysicalForce
{
public:
    GravitationForce(double gravConst, double xdir, double ydir, double zdir, PhysicalObject *obj);

    virtual Vector3 approxM(PhysicalObject *caller) const;
private:
    PhysicalObject *obj;
    double g;
    Vector3 gVec;
};

#endif // GRAVITATIONFORCE_H
