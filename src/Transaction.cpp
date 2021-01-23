#include "Transaction.h"

Transaction::Transaction()
{
//    this->bookNode = bookNode;
 //   this->memberNode = memberNode;
}

Transaction::~Transaction()
{
    //dtor
}

int Transaction::getID(){
    return ID;
}

void Transaction::setID(int ID)
{
    this->ID = ID;
}

void Transaction::setBookID(int BookID)
{
    this->BookID = BookID;
}

void Transaction::setMemberID(int MemberID)
{
    this->MemberID = MemberID;
}

int Transaction::getBookID()
{
return BookID;
}

int Transaction::getMemberID()
{
return MemberID;
}

void Transaction::setDateBorrowed(string date){
    this->dateBorrowed = date;
}

string Transaction::getDateBorrowed(){
    return dateBorrowed;
}
