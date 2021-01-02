#include "Library.h"

Library::Library(BooksCoordinator *booksCoordinator)
{
    this->booksCoordinator = booksCoordinator;
}

Library::~Library()
{
    booksCoordinator = NULL;
    delete booksCoordinator;
}

char Library::showMenu()
{
    char choice;
    system("cls");
    cout << "----- WYBIERZ OPCJE Z MENU -----\n\n";
    cout<<"1. Wyœwietl wszystkie pozycje\n";
    cout<<"2. Dodaj ksiazke\n";
    cout<<"3. Wyszukaj ksiazke\n";
    cout<<"4. Wyswietl wypozyczajacych\n";
    cout<<"5. Edytuj pozycje\n";
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

void Library::editBook()
{
    booksCoordinator->editBook();
}

bool Library::searchForBook(){}

void Library::showMembers(){}

void Library::booksMenu(){}
