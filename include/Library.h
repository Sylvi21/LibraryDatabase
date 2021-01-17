#ifndef LIBRARY_H
#define LIBRARY_H
#include "BooksCoordinator.h"
#include "MembersCoordinator.h"
#include "DataManipulation.h"
#include <iostream>

using namespace std;

class Library
{
    private:
        MembersCoordinator *membersCoordinator;
        BooksCoordinator *booksCoordinator;
        //TransactionsCoordinator *transactions;
    public:
        Library(BooksCoordinator *booksCoordinator);
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
