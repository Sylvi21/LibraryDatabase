#include "TransactionsDB.h"

TransactionsDB::TransactionsDB()
{
    //ctor
}

TransactionsDB::~TransactionsDB()
{
    //dtor
}

TransactionNode* TransactionsDB::getFront()
{
    return firstOfTransactions;
}

TransactionNode* TransactionsDB::getBack()
{
    return lastOfTransactions;
}

TransactionNode* TransactionsDB::loadTransactionsFromFile()
{
}
