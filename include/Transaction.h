#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "BooksStruct.h"
#include "MembersStruct.h"

using namespace std;

class Transaction
{
    private:
        int ID;
        int BookID;
        int MemberID;
    public:
        Transaction();
        virtual ~Transaction();
        int getID();
        string getDateBorrowed();
        string getDueDate();
        void setDateBorrowed(string date);
        void setDueDate(string date);
        void setStatus();
        void setID(int ID);
        void setBookID(int BookID);
        void setMemberID(int MemberID);
        int getBookID();
        int getMemberID();
};

#endif // TRANSACTION_H
