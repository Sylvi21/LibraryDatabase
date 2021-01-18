#include "TransactionsCoordinator.h"

TransactionsCoordinator::TransactionsCoordinator(TransactionsDB *transactionsDB)
{
    this->transactionsDB = transactionsB;
    this->firstOfTransactions = transactionsDB->loadBooksFromFile();
    this->lastOfTransactions = firstOfTransactions;
    while(lastOfTransactions != NULL){
        if(lastOfTransactions->next == NULL)
            break;
        lastOfTransactions=lastOfTransactions->next;
    }
}

TransactionsCoordinator::~TransactionsCoordinator()
{
    //dtor
}
