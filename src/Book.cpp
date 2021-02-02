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
    while(authorsName.length() > 21 || authorsName.length() < 3){
        cout<<"Imie musi zawierac min. 2 i max. 20 znakow. Podaj ponownie: "<<endl;
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
    while(authorsSurname.length() > 21 || authorsSurname.length() < 3){
        cout<<"Nazwisko musi zawierac min. 2 i max. 20 znakow. Podaj ponownie: "<<endl;
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
    while(title.length() > 21 || title.length() < 3){
        cout<<"Tytul musi zawierac min. 2 i max. 20 znakow. Podaj ponownie: "<<endl;
        title = DataManipulation::loadLine();
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
        cout<<"Rok wydania musi sie zawierac pomiedzy 0 a "<<DataManipulation::getCurrentYear()<<". Podaj ponownie: "<<endl;
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
        cout<<"Podano bledny numer ISBN. Podaj ponownie: "<<endl;
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
    while(genre.empty()){
        cout<<"Musisz podac gatunek: "<<endl;
        genre = DataManipulation::loadLine();
    }
    this->genre = genre;
}

string Book::getStatus()
{
    return status;
}

void Book::setStatus(string status)
{
    cout<<"Status:"<<status<<endl;
    while(status != "dostepna" && status != "zarezerwowana" && status != "wypozyczona"){
        cout<<"Bledny status. Mozliwe opcje: dostepna, zarezerwowana, wypozyczona."<<endl;
        status = DataManipulation::loadLine();
    }
    this->status = status;
}

bool Book::isISBNValid(string ISBN){
    ISBN.erase(remove(ISBN.begin(), ISBN.end(), '-'), ISBN.end());

    if(ISBN.length() == 10){
        return true;
    } else if (ISBN.length() == 13){
        return true;
    } else
        return false;
}
