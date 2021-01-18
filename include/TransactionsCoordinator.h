#ifndef TRANSACTIONSCOORDINATOR_H
#define TRANSACTIONSCOORDINATOR_H
#include "TransactionsStruct.h"
#include "TransactionsDB.h"
#include "DataManipulation.h"
#include <conio.h>
class TransactionsCoordinator
{
    private:
        TransactionsDB *transactionsDB;
        TransactionNode* firstOfTransactions;
        TransactionNode* lastOfTransactions;
    public:

        TransactionsCoordinator(TransactionsDB *transactionsDB);
        virtual ~TransactionsCoordinator();
        void lendBook();
        void registerReturn();
        void showTransactions();
        void showOverdue();

#endif // TRANSACTIONSCOORDINATOR_H
