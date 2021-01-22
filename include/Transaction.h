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
        string dateBorrowed;
        string dueDate;
    public:
        Transaction();
        virtual ~Transaction();
        int getID();
        void setID(int ID);
        void setBookID(int BookID);
        void setMemberID(int MemberID);
        int getBookID();
        int getMemberID();
        string getDateBorrowed();
        string getDueDate();
        void setDateBorrowed(string date);
        void setDueDate(string date);
        void setStatus();
};

#endif // TRANSACTION_H
