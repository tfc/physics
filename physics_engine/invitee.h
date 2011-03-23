#ifndef INVITEE_H
#define INVITEE_H

#include "physics_engine/inviter.h"

class Invitee
{
public:
    Invitee();

    virtual void invite(Inviter* host) { host->visit(this); }
};

#endif // INVITEE_H
