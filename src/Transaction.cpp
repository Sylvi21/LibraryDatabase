#include "Transaction.h"

Transaction::Transaction(BookNode *bookNode, MemberNode *memberNode)
{
    this->bookNode = bookNode;
    this->memberNode = memberNode;
}

Transaction::~Transaction()
{
    //dtor
}

int Transaction::getID(){
    return ID;
}
