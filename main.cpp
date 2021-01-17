#include "Library.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "BooksStruct.h"
#include "BooksDB.h"
#include "BooksCoordinator.h"
#include "Library.h"

using namespace std;

int main()
{
    BooksDB *booksDB = new BooksDB();
    BooksCoordinator *booksCoordinator = new BooksCoordinator(booksDB);
    Library library(booksCoordinator);
    char choice;

    while(true)
    {
        choice = library.showMainMenu();
        switch(choice)
        {
            case '1': {
                choice = library.showTransactionsMenu();
                switch(choice)
                {
                    case '1': {
                        library.lendBook();
                        break;
                    }
                    case '2':{
                        library.registerReturn();
                        break;
                    }
                    case '3': {
                        library.showTransactions();
                        break;
                    }
                    case '4': {
                        library.showOverdue();
                        break;
                    }
                    case '5': {
                        break;
                    }
                    default:
                        cout<< "Nie ma takiej opcji w menu. Wybierz jeszcze raz.\n";
                }
                break;
            }
            case '2': {
                choice = library.showBooksMenu();
                switch(choice)
                {
                    case '1': {
                        library.showBooksList();
                        break;
                    }
                    case '2':{
                        library.addNewBook();
                        break;
                    }
                    case '3': {
                        library.searchForBook();
                        break;
                    }
                    case '4':{
                        library.editBook();
                        break;
                    }
                    case '5': {
                        library.removeBook();
                        break;
                    }
                    case'6': {
                        break;
                    }
                    default:
                        cout<< "Nie ma takiej opcji w menu. Wybierz jeszcze raz.\n";
                }
                break;
            }
            case '3': {
                choice = library.showMembersMenu();
                switch(choice)
                {
                    case '1': {
                        library.showMembers();
                        break;
                    }
                    case '2':{
                        library.addNewMember();
                        break;
                    }
                    case '3': {
                        library.searchForMember();
                        break;
                    }
                    case '4': {
                        library.editMember();
                        break;
                    }
                    case '5': {
                        library.removeMember();
                        break;
                    }
                    case '6': {
                        break;
                    }
                    default:
                        cout<< "Nie ma takiej opcji w menu. Wybierz jeszcze raz.\n";
                }
                break;
            }
            case'4': {
                cout << "Koniec pracy programu.";
                exit(0);
            }
            default:
                cout<< "Nie ma takiej opcji w menu. Wybierz jeszcze raz.\n";
        }
    }
    return 0;
}

