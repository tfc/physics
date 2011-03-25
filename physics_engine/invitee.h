#ifndef INVITEE_H
#define INVITEE_H

#include "inviter.h"

class Invitee
{
public:
    Invitee();

    virtual void invite(class Inviter &host) = 0;
};

#endif // INVITEE_H
