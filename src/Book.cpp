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
    return id;
}

void Book::setID(int id)
{
    this->id = id;
}

std::string Book::getAuthorsName()
{
    return authorsName;
}

void Book::setAuthorsName(std::string authorsName)
{
    this->authorsName = authorsName;
}

std::string Book::getAuthorsSurname()
{
    return authorsSurname;
}

void Book::setAuthorsSurname(std::string authorsSurname)
{
    this->authorsSurname = authorsSurname;
}

std::string Book::getTitle()
{
    return title;
}

void Book::setTitle(std::string title)
{
    this->title = title;
}

std::string Book::getYearPublished()
{
    return yearPublished;
}

void Book::setYearPublished(std::string yearPublished)
{
    this->yearPublished = yearPublished;
}

std::string Book::getGenre()
{
    return genre;
}

void Book::setGenre(std::string genre)
{
    this->genre = genre;
}
