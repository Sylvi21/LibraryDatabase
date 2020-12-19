#include "BooksDB.h"

BooksDB::BooksDB()
{

}

BooksDB::~BooksDB()
{
    //dtor
}

BooksDB::getLastBookID(){
    return lastBookID;
}
bool BooksDB::addBookToDB(Book book)
{
    std::fstream booksDB;
    booksDB.open(filename.c_str(), std::ios::app);
    if (booksDB.good() == true)
    {
        booksDB<<book.getAuthorsName()<<"|";
        booksDB<<book.getAuthorsSurname()<<"|";
        booksDB<<book.getTitle()<<"|";
        booksDB<<book.getYearPublished()<<"|";
        booksDB<<book.getGenre()<<"|"<<std::endl;
        booksDB.close();

        lastBookID++;
    }
    else
    {
        std::cout<<"Nie udalo sie otworzyc pliku i zapisac do niego danych. ";
    }
}
