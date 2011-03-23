#ifndef INVITER_H
#define INVITER_H

class Invitee;

class Inviter
{
public:
    Inviter();

    virtual void visit(class PhysicalObject &) {}
    virtual void visit(class PhysicalForce &) {}
};

#endif // INVITER_H
