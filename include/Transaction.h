#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "Book.h"
#include "Member.h"

class Transaction
{
    private:
        int ID;
        Book *book;
        Member *member;
        string dateBorrowed;
        string dueDate;
        string status;
    public:
        Transaction();
        Transaction(Book *book, Member *member);
        virtual ~Transaction();

};

#endif // TRANSACTION_H
