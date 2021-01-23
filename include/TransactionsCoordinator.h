#ifndef TRANSACTIONSCOORDINATOR_H
#define TRANSACTIONSCOORDINATOR_H
#include "TransactionsStruct.h"
#include "TransactionsDB.h"
#include "DataManipulation.h"
#include <conio.h>
#include <time.h>

using namespace std;

class TransactionsCoordinator
{
    private:
        TransactionsDB *transactionsDB;
        TransactionNode* firstOfTransactions;
        TransactionNode* lastOfTransactions;

        string getCurrentDate();
        void showSingleTransaction(TransactionNode *transaction);
        void addSingleTransaction(TransactionNode *transaction);
    public:

        TransactionsCoordinator(TransactionNode* firstOfTransactions, TransactionNode* lastOfTransactions, TransactionsDB *transactionsDB);
        virtual ~TransactionsCoordinator();
        TransactionNode* findSpot(TransactionNode transaction);
        void lendBook(Member *memberNode, Book *bookNode);
        void aquireObjectsByID(MemberNode *frontMemberNode, BookNode *frontBookNode);
        void registerReturn();
        void showTransactions();
        void showOverdue();
};

#endif // TRANSACTIONSCOORDINATOR_H
