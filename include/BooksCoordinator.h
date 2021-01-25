#ifndef BOOKSCOORDINATOR_H
#define BOOKSCOORDINATOR_H
#include "BooksStruct.h"
#include "BooksDB.h"
#include "DataManipulation.h"
#include <conio.h>

using namespace std;

class BooksCoordinator
{
    private:
        BooksDB *booksDB;
        BookNode* firstOfBooks;
        BookNode* lastOfBooks;

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
        void deleteBook(BookNode* node);
    public:
        BooksCoordinator(BookNode *firstOfBooks, BookNode *lastOfBooks, BooksDB *booksDB);
        virtual ~BooksCoordinator();
        void showBooksList();
        void addNewBook();
        Book getSingleBook(int bookId);
        Book setBookData();
        BookNode* findSpot(Book book);
        BookNode* getBookNode(int Id);
        void searchForBook();
        bool setBookAsAvailable(Book* book);
        void editBook();
        void removeBook();
};

#endif // BOOKSCOORDINATOR_H
