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

char Library::showMainMenu()
{
    char choice;
    system("cls");
    cout << "----- MENU GLOWNE BIBLIOTEKI -----\n\n";
    cout<<"1. Menu wypozyczen\n";
    cout<<"2. Menu ksiazek\n";
    cout<<"3. Menu czlownkow\n";
    cout<<"4. Zakoncz program\n";

    choice = DataManipulation::loadCharacter();
    return choice;
}

char Library::showTransactionsMenu(){
    char choice;
    system("cls");
    cout << "----- MENU TRANSAKCJI -----\n\n";
    cout<<"1. Zarejestruj wypozyczenie\n";
    cout<<"2. Zarejestruj zwrot\n";
    cout<<"3. Wyswietl wszystkie wypozyczenia\n";
    cout<<"4. Wyswietl opoznienia w zwrocie\n";
    cout<<"8. Wyjscie\n";

    choice = DataManipulation::loadCharacter();
    return choice;
}

char Library::showBooksMenu(){
    char choice;
    system("cls");
    cout << "----- MENU KSIAZEK -----\n\n";
    cout<<"1. Wyœwietl wszystkie ksiazki\n";
    cout<<"2. Dodaj ksiazke\n";
    cout<<"3. Wyszukaj ksiazke\n";
    cout<<"4. Edytuj ksiazke\n";
    cout<<"5. Usun ksiazke\n";
    cout<<"6. Wyjscie\n";

    choice = DataManipulation::loadCharacter();
    return choice;
}

char Library::showMembersMenu(){
    char choice;
    system("cls");
    cout << "----- MENU CZYTELNIKOW -----\n\n";
    cout<<"1. Wyswietl wszsytkich czytelnikow\n";
    cout<<"2. Dodaj czytelnika\n";
    cout<<"3. Wyszukaj czytelnika\n";
    cout<<"4. Edytuj czytelnika\n";
    cout<<"5. Usun czytelnika\n";
    cout<<"6. Wyjscie\n";

    choice = DataManipulation::loadCharacter();
    return choice;
}

void Library::lendBook()
{

}

void Library::registerReturn()
{

}

void Library::showTransactions()
{

}

void Library::showOverdue()
{

}

void Library::showMembers()
{
    membersCoordinator->showMembersList();
}

void Library::addNewMember()
{
    membersCoordinator->addNewMember();
}

void Library::searchForMember()
{
    membersCoordinator->searchForMember();
}

void Library::editMember()
{
    membersCoordinator->editMember();
}

void Library::removeMember()
{
    membersCoordinator->removeMember();
}

void Library::showBooksList()
{
    booksCoordinator->showBooksList();
}

void Library::addNewBook()
{
    booksCoordinator->addNewBook();
}

void Library::searchForBook()
{
    booksCoordinator->searchForBook();
}

void Library::editBook()
{
    booksCoordinator->editBook();
}

void Library::removeBook()
{
    booksCoordinator->removeBook();
}
