#ifndef INVITER_H
#define INVITER_H

#include <iostream>

class Invitee;

class Inviter
{
public:
    Inviter();

    virtual void visit(class PhysicalObject &) { std::cout << "a";}
    virtual void visit(class PhysicalForce &) { std::cout << "b"; }
    virtual void visit(class RopeForce &) { std::cout << "c"; }
    virtual void visit(class GravitationForce &) {}

};

#endif // INVITER_H
