#ifndef TRANSACTIONSSTRUCT_H
#define TRANSACTIONSSTRUCT_H
#include "Transaction.h"

struct TransactionNode {
    MemberNode *memberNode;
    BookNode *bookNode;
    TransactionNode *prev;
    TransactionNode *next;
};

#endif // TRANSACTIONSSTRUCT_H
