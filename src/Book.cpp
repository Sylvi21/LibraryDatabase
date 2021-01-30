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
    while(authorsName.length() > 20){
        cout<<"Podane imie jest za dlugie. Maksymalna ilosc znakow to 20. Podaj ponownie: "<<endl;
        authorsName = DataManipulation::loadLine();
    }
    this->authorsName = authorsName;
}

string Book::getAuthorsSurname()
{
    return authorsSurname;
}

void Book::setAuthorsSurname(string authorsSurname)
{
    while(authorsSurname.length() > 20){
        cout<<"Podane Nazwisko jest za dlugie. Maksymalna ilosc znakow to 20. Podaj ponownie: "<<endl;
        authorsSurname = DataManipulation::loadLine();
    }
    this->authorsSurname = authorsSurname;
}

string Book::getTitle()
{
    return title;
}

void Book::setTitle(string title)
{
    while(title.length() > 20){
        cout<<"Podane Nazwisko jest za dlugie. Maksymalna ilosc znakow to 20. Podaj ponownie: "<<endl;
        authorsName = DataManipulation::loadLine();
    }
    this->title = title;
}

int Book::getYearPublished()
{
    return yearPublished;
}

void Book::setYearPublished(int yearPublished)
{
    while(yearPublished < 0 && yearPublished > DataManipulation::getCurrentYear()){
        cout<<"Podane Nazwisko jest za dlugie. Maksymalna ilosc znakow to 20. Podaj ponownie: "<<endl;
        yearPublished = DataManipulation::loadInteger();
    }
    this->yearPublished = yearPublished;
}

string Book::getISBN()
{
    return ISBN;
}

void Book::setISBN(string ISBN)
{
    while(!isISBNValid(ISBN)){
        cout<<"Podano bledny numer ISBN: "<<endl;
        authorsName = DataManipulation::loadLine();
    }
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

bool Book::isISBNValid(string ISBN){
    return true;
}
