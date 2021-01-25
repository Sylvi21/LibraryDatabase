#ifndef BOOKSDB_H
#define BOOKSDB_H
#include "Book.h"
#include "DataManipulation.h"
#include <iostream>
#include <fstream>
#include "BooksStruct.h"

using namespace std;

class BooksDB
{
    private:
        string booksFileName = "Books.txt";
        int lastBookID;
        BookNode *firstOfBooks;
        BookNode *lastOfBooks;
    public:
        BooksDB();
        virtual ~BooksDB();
        BookNode* getFront();
        BookNode* getBack();
        void loadBooksFromFile();
        BookNode* findSpot(BookNode* books, Book book);
        int getLastBookID();
        int setLastBookID(string dataLine);
        string getFilename();
        bool addBookToDB(Book book);
        Book getSingleBookFromFile(string dataLine, int lastBookID);
        bool editBookInDB(Book book);
        void removeBookFromDB(int ID);
};

#endif // BOOKSDB_H
