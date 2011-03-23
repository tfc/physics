#ifndef INVITER_H
#define INVITER_H

class Invitee;

class Inviter
{
public:
    Inviter();

    virtual void visit(Invitee* guest) = 0;
};

#endif // INVITER_H
