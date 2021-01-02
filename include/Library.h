#ifndef LIBRARY_H
#define LIBRARY_H
#include "BooksCoordinator.h"
#include "DataManipulation.h"
#include <iostream>

using namespace std;

class Library
{
    private:
        //MembersCoordinator *membersCoordinator;
        BooksCoordinator *booksCoordinator;
        //TransactionsCoordinator *transactions;
    public:
        Library(BooksCoordinator *booksCoordinator);
        virtual ~Library();

        char showMenu();
        void showBooksList();
        void addNewBook();
        void searchByAuthor();
        bool searchForBook();
        void showMembers();
        void booksMenu();
        void editBook();
};

#endif // LIBRARY_H
