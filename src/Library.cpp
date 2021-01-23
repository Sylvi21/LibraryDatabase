#include "Library.h"

Library::Library(BooksCoordinator *books, MembersCoordinator *members, TransactionsCoordinator *transactions)
{
    this->books = books;
    this->members = members;
    this->transactions = transactions;
}

Library::~Library()
{
    delete books;
    books = NULL;
    delete members;
    members = NULL;
    delete transactions;
    transactions = NULL;
}

char Library::showMainMenu()
{
    char choice;
    system("cls");
    cout << "----- MENU GLOWNE BIBLIOTEKI -----\n\n";
    cout<<"1. Menu wypozyczen\n";
    cout<<"2. Menu ksiazek\n";
    cout<<"3. Menu czytelnikow\n";
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
    cout<<"1. Wyswietl wszystkie ksiazki\n";
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
    cout<<"1. Wyswietl wszystkich czytelnikow\n";
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
    system("cls");
    cout<<"Podaj ID czytelnika, ktory chce wypozyczyc ksiazke: ";
    int memberId = DataManipulation::loadInteger();

    Member *member = &(members->getMemberNode(memberId)->member);
    if (member == NULL){
        cout<<"Wystapil blad. Nie udalo sie znalezc uzytkownika.\n";
        return;
    }

    cout<<"Podaj ID ksiazki, ktora bedzie wypozyczona: ";
    int bookId = DataManipulation::loadInteger();

    Book *book = &(books->getBookNode(bookId)->book);
    if (book == NULL){
        cout<<"Wystapil blad. Nie udalo sie dodac ksiazki.\n";
        return;
    }
    transactions->lendBook(&*member, &*book);
}

void Library::registerReturn()
{
    system("cls");
    cout<<"Podaj ID uzytkownika zwracaj¹cego ksiazke: ";
    int memberId = DataManipulation::loadInteger();

    transactions->showTransactionsByMember(memberId);
    cout<<"Wybierz ID wypozyczenia: ";
    int transactionId = DataManipulation::loadInteger();

    transactions->registerReturn(transactionId);
}

void Library::showTransactions()
{
    transactions->showTransactions();
}

void Library::showOverdue()
{
    transactions->showOverdue();
}

void Library::showMembers()
{
    members->showMembersList();
}

void Library::addNewMember()
{
    members->addNewMember();
}

void Library::searchForMember()
{
    members->searchForMember();
}

void Library::editMember()
{
    members->editMember();
}

void Library::removeMember()
{
    members->removeMember();
}

void Library::showBooksList()
{
    books->showBooksList();
}

void Library::addNewBook()
{
    books->addNewBook();
}

void Library::searchForBook()
{
    books->searchForBook();
}

void Library::editBook()
{
    books->editBook();
}

void Library::removeBook()
{
    books->removeBook();
}
