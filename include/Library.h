#ifndef LIBRARY_H
#define LIBRARY_H
#include "BooksCoordinator.h"
#include "MembersCoordinator.h"
#include "TransactionsCoordinator.h"
#include "DataManipulation.h"
#include <iostream>
#include "MembersStruct.h"

using namespace std;

class Library
{
    private:
        MembersCoordinator *members;
        BooksCoordinator *books;
        TransactionsCoordinator *transactions;
    public:
        Library(BooksCoordinator *books, MembersCoordinator *members, TransactionsCoordinator *transactions);
        virtual ~Library();

        char showMainMenu();
        char showTransactionsMenu();
        char showMembersMenu();
        char showBooksMenu();

        void lendBook();
        void registerReturn();
        void showTransactions();
        void showOverdue();

        void showBooksList();
        void addNewBook();
        void searchForBook();
        void editBook();
        void removeBook();

        void showMembers();
        void addNewMember();
        void searchForMember();
        void editMember();
        void removeMember();
};

#endif // LIBRARY_H
