#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "BooksStruct.h"
#include "MembersStruct.h"

using namespace std;

class Transaction
{
    private:

    public:
        Transaction(BookNode *bookNode, MemberNode *memberNode);
        virtual ~Transaction();
        int getID();
        string getDateBorrowed();
        string getDueDate();
        void setDateBorrowed(string date);
        void setDueDate(string date);
        void setStatus();
};

#endif // TRANSACTION_H
