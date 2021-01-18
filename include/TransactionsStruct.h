#ifndef TRANSACTIONSSTRUCT_H
#define TRANSACTIONSSTRUCT_H
#include "Transaction.h"

struct TransactionNode {
    Transaction Transaction;
    TransactionNode *prev;
    TransactionNode *next;
};

#endif // TRANSACTIONSSTRUCT_H
