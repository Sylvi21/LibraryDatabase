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
    while(memberName.length() > 21 || memberName.length() < 3){
        cout<<"Imie musi zawierac min. 2 i max. 20 znakow. Podaj ponownie: "<<endl;
        memberName = DataManipulation::loadLine();
    }
    this->memberName = memberName;
}

string Member::getMemberSurname()
{
    return memberSurname;
}

void Member::setMemberSurname(string memberSurname)
{
    while(memberSurname.length() > 21 || memberSurname.length() < 3){
        cout<<"Nazwisko musi zawierac min. 2 i max. 20 znakow. Podaj ponownie: "<<endl;
        memberSurname = DataManipulation::loadLine();
    }
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
    while(memberStreet.length() > 21 || memberStreet.length() < 3){
        cout<<"Nazwa ulicy musi zawierac min. 2 i max. 20 znakow. Podaj ponownie: "<<endl;
        memberStreet = DataManipulation::loadLine();
    }
    this->memberStreet = memberStreet;
}

string Member::getMemberNumber()
{
    return memberNumber;
}

void Member::setMemberNumber(string memberNumber)
{
    while(memberNumber.length() > 6 || memberNumber.length() < 3){
        cout<<"Nazwa ulicy musi zawierac min. 2 i max. 5 znakow. Podaj ponownie: "<<endl;
        memberNumber = DataManipulation::loadLine();
    }
    this->memberNumber = memberNumber;
}

string Member::getMemberZIP()
{
    return memberZIP;
}

void Member::setMemberZIP(string memberZIP)
{
    while(memberZIP.length() > 6 || memberZIP.length() < 3){
        cout<<"Nazwa ulicy musi zawierac min. 2 i max. 5 znakow. Podaj ponownie: "<<endl;
        memberZIP = DataManipulation::loadLine();
    }
    this->memberZIP = memberZIP;
}

