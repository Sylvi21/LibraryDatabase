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
    public:
        BooksDB();
        virtual ~BooksDB();
        BookNode* loadBooksFromFile();
        BookNode* findSpot(BookNode* books, Book book);
        int getLastBookID();
        int setLastBookID(string dataLine);
        string getFilename();
        bool addBookToDB(Book book);
        Book getSingleBookFromFile(string dataLine, int lastBookID);
        void editBookInFile(Book book);
};

#endif // BOOKSDB_H
