#ifndef BOOKSCOORDINATOR_H
#define BOOKSCOORDINATOR_H
#include "Book.h"
#include "BooksDB.h"
#include "DataManipulation.h"
#include <conio.h>
#include "BooksStruct.h"

using namespace std;

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
        void showBookDetails(Book book);
        void addNewBook();
        Book getSingleBook(int bookId);
        void searchByAuthor();
        void searchByISBN();
        void searchByGenre();
        void searchByStatus();
        Book setBookData();
        void addAtTheBeginning(Book book);
        bool removeBook();
        bool editBook();
};

#endif // BOOKSCOORDINATOR_H
