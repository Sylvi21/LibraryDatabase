#include "BooksCoordinator.h"

BooksCoordinator::BooksCoordinator(BookNode *firstOfBooks, BookNode *lastOfBooks, BooksDB *booksDB)
{
    this->booksDB = booksDB;
    this->firstOfBooks = firstOfBooks;
    this->lastOfBooks = lastOfBooks;
}

BooksCoordinator::~BooksCoordinator()
{
    BookNode **currentBookNode = &firstOfBooks;
    while(*currentBookNode != NULL){
        BookNode *toDelete = *currentBookNode;
        *currentBookNode = toDelete->next;
        delete toDelete;
        currentBookNode = &(*currentBookNode)->next;
    }
    delete firstOfBooks;
    firstOfBooks = NULL;
    delete lastOfBooks;
    lastOfBooks = NULL;

}

void BooksCoordinator::showSingleBook(Book book){
    cout<<book.getID()<<" "<<
    book.getAuthorsName()<<" "<<
    book.getAuthorsSurname()<<" "<<
    book.getTitle()<<" "<<
    book.getYearPublished()<<" "<<
    book.getISBN()<<" "<<
    book.getGenre()<<" "<<
    book.getStatus()<<endl;
}

void BooksCoordinator::showBooksList(){
    BookNode* currentBookNode = firstOfBooks;
    system("cls");
    cout<<"-----KSIAZKI-----\n\n";
    if (currentBookNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj ksiazki."<<"\n";
    else
    {
        while(currentBookNode != NULL){
            showSingleBook(currentBookNode->book);
            currentBookNode = currentBookNode->next;
        }
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::showBookDetails(Book book){
    cout<<"Id: "<<book.getID()<<endl;
    cout<<"Imiona: "<<book.getAuthorsName()<<endl;
    cout<<"Nazwisko: "<<book.getAuthorsSurname()<<endl;
    cout<<"Tytu³: "<<book.getTitle()<<endl;
    cout<<"Rok wydania: "<<book.getYearPublished()<<endl;
    cout<<"Numer ISBN: "<<book.getISBN()<<endl;
    cout<<"Gatunek: "<<book.getGenre()<<endl;
    cout<<"Status: "<<book.getStatus()<<endl<<endl;
}

Book BooksCoordinator::setBookData(){
    Book book;
    int yearPublished;
    string authorName, authorSurname, title, ISBN, genre, status;
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
    yearPublished = DataManipulation::loadInteger();
    book.setYearPublished(yearPublished);

    cout << "Podaj numer ISBN: \n";
    ISBN = DataManipulation::loadLine();
    book.setISBN(ISBN);

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

void BooksCoordinator::searchForBook()
{
    BookNode* currentBookNode = firstOfBooks;
    bool bookExists = false;
    char searchChoice;
    string newData;

    system("cls");
    cout<<"WYSZUKAJ POZYCJE\n\n";

    if (currentBookNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Wybierz wg czego chcesz prowadziæ poszukiwania: \n";
        cout << "1. Imie/Imiona\n";
        cout << "2. Imie/Imiona\n";
        cout << "3. Nazwisko\n";
        cout << "4. Tytul\n";
        cout << "5. Rok wydania\n";
        cout << "6. Gatunek\n";
        cout << "7. ISBN\n";
        cout << "8. Status\n";

        searchChoice = DataManipulation::loadCharacter();

        switch(searchChoice)
        {
        case '1':
            searchByID(DataManipulation::loadInteger());
            break;
        case '2':
            searchByName(DataManipulation::loadLine());
            break;
        case '3':
            searchBySurname(DataManipulation::loadLine());
            break;
        case '4':
            searchByTitle(DataManipulation::loadLine());
            break;
        case '5':
            searchByYear(DataManipulation::loadInteger());
            break;
        case '6':
            searchByGenre(DataManipulation::loadLine());
            break;
        case '7':
            searchByISBN(DataManipulation::loadLine());
            break;
        case '8':
            searchByStatus(DataManipulation::loadLine());
            break;
        }
    }
    cout<<"Kliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByID(int ID)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O ID "<<ID<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getID() == ID){
            showBookDetails(currentBookNode->book);
            found = true;
            break;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji o ID = "<<ID<<endl<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByName(string name)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI NAPISANE PRZEZ "<<name<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getAuthorsName() == name){
            showBookDetails(currentBookNode->book);
            found = true;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchBySurname(string surname)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI NAPISANE PRZEZ "<<surname<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getAuthorsSurname() == surname){
            showBookDetails(currentBookNode->book);
            found = true;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByTitle(string title)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O TYTULE "<<title<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getTitle() == title){
            showBookDetails(currentBookNode->book);
            found = true;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByYear(int yearPublished)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI WYDANE W "<<yearPublished<<" ROKU -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getYearPublished() == yearPublished){
            showBookDetails(currentBookNode->book);
            found = true;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByGenre(string genre)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI Z GATUNKU "<<genre<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getGenre() == genre){
            showBookDetails(currentBookNode->book);
            found = true;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByISBN(string ISBN)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O NUMERZE ISBN "<<ISBN<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getISBN() == ISBN){
            showBookDetails(currentBookNode->book);
            found = true;
            break;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByStatus(string status)
{
    BookNode* currentBookNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O STATUSIE "<<status<<" -----\n\n";
    while(currentBookNode != NULL){
        if(currentBookNode->book.getStatus() == status){
            showBookDetails(currentBookNode->book);
            found = true;
        }
        currentBookNode = currentBookNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentBookNode = NULL;
    delete currentBookNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

BookNode* BooksCoordinator::getBookNode(int Id)
{
    BookNode* currentBookNode = firstOfBooks;
    while(currentBookNode != NULL && currentBookNode->book.getID() != Id)
        currentBookNode=currentBookNode->next;
    return currentBookNode;
}

BookNode* BooksCoordinator::findSpot(Book book)
{
    BookNode* currentBookNode = firstOfBooks;
    while(currentBookNode != NULL && currentBookNode->book.getAuthorsSurname() < book.getAuthorsSurname())
        currentBookNode=currentBookNode->next;
    return currentBookNode;
}

void BooksCoordinator::addSingleBook(Book book)
{
    BookNode* pom = NULL;
    BookNode* temp = new BookNode();
    temp = NULL;
    BookNode* newBookNode = new BookNode();
    newBookNode->book = book;

    if (firstOfBooks == NULL) {
        firstOfBooks = newBookNode;
        lastOfBooks = newBookNode;
        newBookNode->prev = NULL;
        newBookNode->next = NULL;
    } else {
        temp = findSpot(book);
        if(firstOfBooks == temp){
            newBookNode->next = firstOfBooks;
            firstOfBooks->prev = newBookNode;
            newBookNode->prev = NULL;
            firstOfBooks = newBookNode;
        } else if (temp == NULL){
            lastOfBooks->next = newBookNode;
            newBookNode->prev = lastOfBooks;
            newBookNode->next = temp;
            lastOfBooks = newBookNode;
        } else {
            pom=temp->prev;
            pom->next=newBookNode;
            newBookNode->prev=temp->prev;
            temp->prev=newBookNode;
            newBookNode->next=temp;
        }
        temp = NULL;
        delete temp;
        pom = NULL;
        delete pom;
    }
}

void BooksCoordinator::editBook(){
    BookNode* currentBookNode = firstOfBooks;
    int searchedID;
    bool bookExists = false;
    char choice;
    string newData;

    system("cls");
    cout<<"EDYTUJ KSIAZKE\n\n";

    if (currentBookNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Podaj ID ksiazki do edytowania: ";
        searchedID = DataManipulation::loadInteger();

        while(currentBookNode != NULL)
        {
            if(currentBookNode->book.getID() == searchedID)
            {
                bookExists = true;
                showBookDetails(currentBookNode->book);

                cout<<"Wybierz dane do zmiany: \n\n";
                cout<<"1. Imie\n";
                cout<<"2. Nazwisko\n";
                cout<<"3. Tytul\n";
                cout<<"4. Rok wydania\n";
                cout<<"5. Numer ISBN\n";
                cout<<"6. Gatunek\n";
                cout<<"7. Status\n\n";

                choice = DataManipulation::loadCharacter();

                switch(choice)
                {
                case '1':
                    cout<<"Podaj nowe imie/imiona: ";
                    currentBookNode->book.setAuthorsName(DataManipulation::loadLine());
                    break;
                case '2':
                    cout<<"Podaj nowe nazwisko: ";
                    currentBookNode->book.setAuthorsSurname(DataManipulation::loadLine());
                    break;
                case '3':
                    cout<<"Podaj nowy tytul: ";
                    currentBookNode->book.setTitle(DataManipulation::loadLine());
                    break;
                case '4':
                    cout<<"Podaj nowy rok wydania: ";
                    currentBookNode->book.setYearPublished(DataManipulation::loadInteger());
                    break;
                case '5':
                    cout<<"Podaj nowy adres zamieszkania ";
                    currentBookNode->book.setISBN(DataManipulation::loadLine());
                    break;
                case '6':
                    cout<<"Podaj nowy adres zamieszkania ";
                    currentBookNode->book.setGenre(DataManipulation::loadLine());
                    break;
                case '7':
                    cout<<"Podaj nowy adres zamieszkania ";
                    currentBookNode->book.setStatus(DataManipulation::loadLine());
                    break;
                case '8':
                    break;
                }
                booksDB->editBookInDB(currentBookNode->book);
                break;
            }
        }
        if (bookExists == false)
        {
            cout<<"Brak pozycji w bazie danych. Dodaj pozycje.\n";
        }
    }
    cout<<"Kliknij dowolny klawisz, aby powrocic.\n";
    getch();
}

void BooksCoordinator::removeBook(){
    BookNode* currentBookNode = firstOfBooks;
    int searchedID;
    bool bookExists = false;
    char choice;
    string newData;

    system("cls");
    cout<<"USUN KSIAZKE\n\n";

    if (currentBookNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Podaj ID ksiazki do usuniecia: ";
        searchedID = DataManipulation::loadInteger();

        while(currentBookNode != NULL)
        {
            if(currentBookNode->book.getID() == searchedID)
            {
                bookExists = true;
                showBookDetails(currentBookNode->book);

                cout<<"Czy na pewno chcesz usunac kontakt?\n"
                "Potwierdz usuniecie klawiszem t. Zrezygnuj klawiszem n.\n";

                choice = DataManipulation::loadCharacter();
                if (choice == 't')
                {
                    deleteBook(currentBookNode);
                    booksDB->removeBookFromDB(searchedID);
                    break;
                }
                else if (choice == 'n')
                    break;
                break;
            }
        }
        if (bookExists == false)
        {
            cout<<"Brak pozycji w bazie danych. Dodaj pozycje.\n";
        }
    }
    cout<<"Kliknij dowolny klawisz, aby powrocic.\n";
    getch();
}

void BooksCoordinator::deleteBook(BookNode* node){
    BookNode *tmp = NULL;
    if(firstOfBooks == NULL)
        return;
    if(node == firstOfBooks){
        firstOfBooks = firstOfBooks->next;
        if(firstOfBooks != NULL)
            firstOfBooks->prev = NULL;
    } else {
        if(node == lastOfBooks){
            lastOfBooks = lastOfBooks->prev;
            if(lastOfBooks != NULL)
                lastOfBooks->next = NULL;
        } else {
            tmp = node->prev;
            tmp->next = tmp->next;
            tmp = node->next;
            tmp->prev = node->prev;
        }
    }
    delete node;
    node = NULL;
    return;
}
