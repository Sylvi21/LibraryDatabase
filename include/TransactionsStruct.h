#ifndef TRANSACTIONSSTRUCT_H
#define TRANSACTIONSSTRUCT_H
#include "Transaction.h"

struct TransactionNode {
    int ID;
    Member *member;
    Book *book;
    string dateBorrowed;
    string dueDate;
    string status;
    TransactionNode *prev;
    TransactionNode *next;
};

#endif // TRANSACTIONSSTRUCT_H
