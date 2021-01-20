#ifndef TRANSACTIONSDB_H
#define TRANSACTIONSDB_H
#include "TransactionsStruct.h"

using namespace std;

class TransactionsDB
{
    private:
    TransactionNode* firstOfTransactions;
    TransactionNode* lastOfTransactions;
    public:
        TransactionsDB();
        virtual ~TransactionsDB();
        TransactionNode* getFront();
        TransactionNode* getBack();
        TransactionNode* loadTransactionsFromFile();
};

#endif // TRANSACTIONSDB_H
