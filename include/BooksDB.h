#ifndef BOOKSDB_H
#define BOOKSDB_H
#include "Book.h"
#include <iostream>
#include <fstream>
#include "BooksStruct.h"

class BooksDB
{
    private:
        const std::string filename = "Books.txt";
        int lastBookID;
    public:
        BooksDB();
        virtual ~BooksDB();
        Node* getAllBooks();
        int getLastBookID();
        bool addBookToDB(Book book);
};

#endif // BOOKSDB_H
