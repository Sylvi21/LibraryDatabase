#ifndef TRANSACTIONSSTRUCT_H
#define TRANSACTIONSSTRUCT_H
#include "Transaction.h"

struct TransactionNode {
    Transaction transaction;
    Member *member;
    Book *book;
    TransactionNode *prev;
    TransactionNode *next;
};

#endif // TRANSACTIONSSTRUCT_H
