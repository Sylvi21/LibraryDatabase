#include "BooksCoordinator.h"

BooksCoordinator::BooksCoordinator(BooksDB *booksDB, Node* Books)
{
    this->booksDB = booksDB;
    this->Books = Books;
}

BooksCoordinator::~BooksCoordinator()
{
    //dtor
}

Book BooksCoordinator::setBookData(){
    Book book;
    std::string authorName, authorSurname, title, yearPublished, genre;
    book.setID(booksDB->getLastBookID()+1);

    std::cout << "Wpisz imie autora: \n";
    authorName = DataManipulation::loadLine();
    book.setAuthorsName(authorName);

    std::cout << "Wpisz nazwisko autora: \n";
    authorSurname = DataManipulation::loadLine();
    book.setAuthorsSurname(authorSurname);

    std::cout << "Wpisz tytul: \n";
    title = DataManipulation::loadLine();
    book.setTitle(title);

    std::cout << "Wpisz rok wydania: \n";
    yearPublished = DataManipulation::loadLine();
    book.setYearPublished(yearPublished);

    std::cout << "Wpisz gatunek: \n";
    genre = DataManipulation::loadLine();
    book.setGenre(genre);

    return book;
}

void BooksCoordinator::addNewBook()
{
    Book book;
    system("cls");
    std::cout << "DODAJ NOWY KONTAKT\n\n";

    book = setBookData();

    if (booksDB->addBookToDB(book))
    {
        addSingleBook(book);
        std::cout << "Pomyslnie dodano pozycje! \n";
    }
    else
        std::cout << "Nie udalo sie dodac pozycji! \n";

    std::cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
    getch();
}

void BooksCoordinator::addSingleBook(Book book){

}

Book BooksCoordinator::getSingleBook(int bookId){

}

void BooksCoordinator::addAtTheBeginning(Book book){

}

bool BooksCoordinator::removeBook(){

}

bool BooksCoordinator::editBook(){

}
