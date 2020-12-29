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
    Node* Books = NULL;
    BooksDB *booksDB = new BooksDB();
    BooksCoordinator *booksCoordinator = new BooksCoordinator(booksDB, Books);
    Library library(booksCoordinator, Books);
    char choice;

    while(true)
    {
        choice = library.showMenu();
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
            if(library.searchForBook())
                library.booksMenu();
            else
                cout << "Nie znaleziono pozycji.";
            break;
        }
        case '4': {
            library.showMembers();
            break;
        }
        case '5': {
            library.searchByAuthor();
            break;
        }
        case'6': {
            cout << "Koniec pracy programu.";
            exit(0);
        }
        default:
            cout<< "Nie ma takiej opcji w menu. Wybierz jeszcze raz.\n";
        }
    }
    return 0;
}

