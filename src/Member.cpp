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
    this->memberName = authorsName;
}

string Book::getMemberSurname()
{
    return memberSurname;
}

void Member::setMemberSurname(string memberSurname)
{
    this->memberSurname = memberSurname;
}

