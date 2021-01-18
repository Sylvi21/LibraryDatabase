#ifndef TRANSACTIONSCOORDINATOR_H
#define TRANSACTIONSCOORDINATOR_H
#include "TransactionsStruct.h"
#include "TransactionsDB.h"
#include "DataManipulation.h"
#include <conio.h>

using namespace std;

class TransactionsCoordinator
{
    private:
        TransactionsDB *transactionsDB;
        TransactionNode* firstOfTransactions;
        TransactionNode* lastOfTransactions;

        void addSingleTransaction(Transaction transaction);
    public:

        TransactionsCoordinator(TransactionsDB *transactionsDB);
        virtual ~TransactionsCoordinator();
        void lendBook(MemberNode *memberNode, BookNode *bookNode);
        void registerReturn();
        void showTransactions();
        void showOverdue();
};
#endif // TRANSACTIONSCOORDINATOR_H
