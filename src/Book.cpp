#include "Book.h"

Book::Book()
{
    //ctor
}

Book::~Book()
{
    //dtor
}

int Book::getID()
{
    return bookID;
}

void Book::setID(int bookID)
{
    this->bookID = bookID;
}

string Book::getAuthorsName()
{
    return authorsName;
}

void Book::setAuthorsName(string authorsName)
{
    this->authorsName = authorsName;
}

string Book::getAuthorsSurname()
{
    return authorsSurname;
}

void Book::setAuthorsSurname(string authorsSurname)
{
    this->authorsSurname = authorsSurname;
}

string Book::getTitle()
{
    return title;
}

void Book::setTitle(string title)
{
    this->title = title;
}

int Book::getYearPublished()
{
    return yearPublished;
}

void Book::setYearPublished(int yearPublished)
{
    this->yearPublished = yearPublished;
}

string Book::getISBN()
{
    return ISBN;
}

void Book::setISBN(string ISBN)
{
    this->ISBN = ISBN;
}

string Book::getGenre()
{
    return genre;
}

void Book::setGenre(string genre)
{
    this->genre = genre;
}

string Book::getStatus()
{
    return status;
}

void Book::setStatus(string status)
{
    this->status = status;
}
