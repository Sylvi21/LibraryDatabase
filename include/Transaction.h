#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "BooksStruct.h"
#include "MembersStruct.h"

using namespace std;

class Transaction
{
    private:
        int ID;
        BookNode *bookNode;
        MemberNode *memberNode;
        string dateBorrowed;
        string dueDate;
        string status;
    public:
        Transaction();
        Transaction(BookNode *bookNode, MemberNode *memberNode);
        virtual ~Transaction();
        void setDateBorrowed(string date);
        void setDueDate(string date);
        void setStatus();
};

#endif // TRANSACTION_H
