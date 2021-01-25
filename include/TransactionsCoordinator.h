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
        TransactionNode* getTransactionById(int id);
        void showSingleTransaction(TransactionNode *transaction);
        void addSingleTransaction(TransactionNode *transaction);
        int removeTransaction(TransactionNode* node);
    public:

        TransactionsCoordinator(TransactionNode* firstOfTransactions, TransactionNode* lastOfTransactions, TransactionsDB *transactionsDB);
        virtual ~TransactionsCoordinator();
        TransactionNode* findSpot(TransactionNode transaction);
        void lendBook(Member *memberNode, Book *bookNode);
        void aquireObjectsByID(MemberNode *frontMemberNode, BookNode *frontBookNode);
        Book* registerReturn(int id);
        void showTransactions();
        bool showTransactionsByMember(int memberId);
        void showOverdue();
};

#endif // TRANSACTIONSCOORDINATOR_H
