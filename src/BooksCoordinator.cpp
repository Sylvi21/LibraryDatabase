#include "BooksCoordinator.h"

BooksCoordinator::BooksCoordinator(BooksDB *booksDB, Node* Books)
{
    this->booksDB = booksDB;
    this->Books = Books;
    this->Books = booksDB->loadBooksFromFile();
}

BooksCoordinator::~BooksCoordinator()
{
    //dtor
}

void BooksCoordinator::showBookDetails(Book book){
    cout<<book.getID()<<" "<<
    book.getAuthorsName()<<" "<<
    book.getTitle()<<" "<<
    book.getYearPublished()<<" "<<
    book.getISBN()<<" "<<
    book.getGenre()<<" "<<
    book.getStatus()<<endl;
}

void BooksCoordinator::showBooksList(){
    system("cls");
    cout<<"-----KSIAZKI-----\n\n";
    if (Books == NULL)
        cout<<"Baza danych jest pusta. Dodaj ksiazki."<<"\n";
    else
    {
        while(Books != NULL){
            showBookDetails(Books->book);
            Books = Books->next;
        }
    }
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

Book BooksCoordinator::setBookData(){
    Book book;
    string authorName, authorSurname, title, yearPublished, genre, status;
    book.setID(booksDB->getLastBookID()+1);

    cout << "Podaj imie autora: \n";
    authorName = DataManipulation::loadLine();
    book.setAuthorsName(authorName);

    cout << "Podaj nazwisko autora: \n";
    authorSurname = DataManipulation::loadLine();
    book.setAuthorsSurname(authorSurname);

    cout << "Podaj tytul: \n";
    title = DataManipulation::loadLine();
    book.setTitle(title);

    cout << "Podaj rok wydania: \n";
    yearPublished = DataManipulation::loadLine();
    book.setYearPublished(yearPublished);

    cout << "Podaj numer ISBN: \n";
    genre = DataManipulation::loadLine();
    book.setGenre(genre);

    cout << "Podaj gatunek: \n";
    genre = DataManipulation::loadLine();
    book.setGenre(genre);

    cout << "Podaj status: \n";
    status = DataManipulation::loadLine();
    book.setStatus(status);

    return book;
}

void BooksCoordinator::addNewBook()
{
    Book book;
    system("cls");
    cout << "DODAJ NOWY KONTAKT\n\n";

    book = setBookData();

    if (booksDB->addBookToDB(book))
    {
        addSingleBook(book);
        cout << "Pomyslnie dodano pozycje! \n";
    }
    else
        cout << "Nie udalo sie dodac pozycji! \n";

    cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
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
