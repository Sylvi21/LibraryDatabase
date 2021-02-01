#include "Member.h"

Member::Member()
{

}

Member::~Member()
{
}

int Member::getID()
{
    return memberID;
}

void Member::setID(int memberID)
{
    this->memberID = memberID;
}

string Member::getMemberName()
{
    return memberName;
}

void Member::setMemberName(string memberName)
{
    this->memberName = memberName;
}

string Member::getMemberSurname()
{
    return memberSurname;
}

void Member::setMemberSurname(string memberSurname)
{
    this->memberSurname = memberSurname;
}

string Member::getMemberTown()
{
    return memberTown;
}

void Member::setMemberTown(string memberTown)
{
    this->memberTown = memberTown;
}

string Member::getMemberStreet()
{
    return memberStreet;
}

void Member::setMemberStreet(string memberStreet)
{
    this->memberStreet = memberStreet;
}

string Member::getMemberNumber()
{
    return memberNumber;
}

void Member::setMemberNumber(string memberNumber)
{
    this->memberNumber = memberNumber;
}

string Member::getMemberZIP()
{
    return memberZIP;
}

void Member::setMemberZIP(string memberZIP)
{
    this->memberZIP = memberZIP;
}

