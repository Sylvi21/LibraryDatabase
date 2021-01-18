#ifndef TRANSACTIONSDB_H
#define TRANSACTIONSDB_H
#include "TransactionsStruct.h"

using namespace std;

class TransactionsDB
{
    private:

    public:
        TransactionsDB();
        virtual ~TransactionsDB();
        TransactionNode* loadTransactionsFromFile();
};

#endif // TRANSACTIONSDB_H
