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
        Node* firstOfBooks;
        Node* lastOfBooks;

        void addSingleBook(Book book);
        void searchByID(int ID);
        void searchByName(string name);
        void searchBySurname(string surname);
        void searchByTitle(string title);
        void searchByYear(int yearPublished);
        void searchByGenre(string genre);
        void searchByISBN(string ISBN);
        void searchByStatus(string status);
        void showSingleBook(Book book);
        void showBookDetails(Book book);
    public:
        BooksCoordinator(BooksDB *booksDB);
        virtual ~BooksCoordinator();
        void showBooksList();
        void addNewBook();
        Book getSingleBook(int bookId);
        Book setBookData();
        Node* findSpot(Book book);
        void searchForBook();
        bool editBook();
        bool removeBook();
};

#endif // BOOKSCOORDINATOR_H
