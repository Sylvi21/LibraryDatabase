#ifndef LIBRARY_H
#define LIBRARY_H
#include "BooksCoordinator.h"
#include "DataManipulation.h"
#include <iostream>

using namespace std;

class Library
{
    private:
        Node *Books;
        Node *Customers;
        CustomersCoordinator;
        BooksCoordinator *booksCoordinator;
    public:
        Library(BooksCoordinator *booksCoordinator, Node *Books);
        virtual ~Library();

        char showMenu();
        void showBooksList();
        void addNewBook();
        void searchByAuthor();
        bool searchForBook();
        void showCustomers();
        void booksMenu();
};

#endif // LIBRARY_H
