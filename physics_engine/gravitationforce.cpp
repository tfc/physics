#include "physics_engine/gravitationforce.h"

GravitationForce::GravitationForce(double gravConst, double xdir, double ydir, double zdir, PhysicalObject *obj) :
    obj(obj), g(gravConst), gVec(xdir, ydir, zdir)
{
    gVec.normalize();
    gVec *= g;

    if (obj) obj->addForce(this);
}

Vector3 GravitationForce::approxM(PhysicalObject *) const
{
    return gVec;
}
