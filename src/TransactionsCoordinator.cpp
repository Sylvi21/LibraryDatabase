#include "TransactionsCoordinator.h"

TransactionsCoordinator::TransactionsCoordinator(TransactionsDB *transactionsDB)
{
    this->transactionsDB = transactionsDB;
    this->firstOfTransactions = transactionsDB->loadTransactionsFromFile();
    this->lastOfTransactions = firstOfTransactions;
    while(lastOfTransactions != NULL){
        if(lastOfTransactions->next == NULL)
            break;
        lastOfTransactions=lastOfTransactions->next;
    }
}

TransactionsCoordinator::~TransactionsCoordinator()
{

}

void TransactionsCoordinator::lendBook(MemberNode *memberNode, BookNode *bookNode)
{

}
void TransactionsCoordinator::registerReturn()
{

}
void TransactionsCoordinator::showTransactions()
{

}
void TransactionsCoordinator::showOverdue()
{

}
