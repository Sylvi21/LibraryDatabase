#include "Library.h"

Library::Library(BooksCoordinator *booksCoordinator, Node* Books)
{
    this->booksCoordinator = booksCoordinator;
    this->Books = NULL;
}

Library::~Library()
{
    delete booksCoordinator;
    booksCoordinator = NULL;
}

char Library::showMenu()
{
    char choice;
    system("cls");
    cout << "----- WYBIERZ OPCJE Z MENU -----\n\n";
    cout<<"1. Wy�wietl wszystkie pozycje\n";
    cout<<"2. Dodaj ksiazke\n";
    cout<<"3. Wyszukaj ksiazke\n";
    cout<<"4. Wyswietl wypozyczajacych\n";
    cout<<"5. Wyswietl \n";
    cout<<"6. Zakoncz program\n";

    choice = DataManipulation::loadCharacter();
    return choice;
}

void Library::showBooksList()
{
    booksCoordinator->showBooksList();
}

void Library::addNewBook()
{
    booksCoordinator->addNewBook();
}

void Library::searchByAuthor()
{

}

bool Library::searchForBook(){}

void Library::showMembers(){}

void Library::booksMenu(){}
