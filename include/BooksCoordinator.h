#ifndef BOOKSCOORDINATOR_H
#define BOOKSCOORDINATOR_H
#include "Book.h"
#include "BooksDB.h"
#include "DataManipulation.h"
#include <conio.h>
#include "BooksStruct.h"

class BooksCoordinator
{
    private:
        BooksDB *booksDB;
        Node* Books;

        void addSingleBook(Book book);
    public:
        BooksCoordinator(BooksDB *booksDB, Node* Books);
        virtual ~BooksCoordinator();
        void showBooksList();
        void addNewBook();
        Book getSingleBook(int bookId);
        void searchByAuthor();
        Book setBookData();
        void addAtTheBeginning(Book book);
        bool removeBook();
        bool editBook();
};

#endif // BOOKSCOORDINATOR_H
