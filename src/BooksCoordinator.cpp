#include "BooksCoordinator.h"

BooksCoordinator::BooksCoordinator(BooksDB *booksDB)
{
    this->booksDB = booksDB;
    this->firstOfBooks = booksDB->loadBooksFromFile();
    this->lastOfBooks = firstOfBooks;
    while(lastOfBooks != NULL){
        if(lastOfBooks->next == NULL)
            break;
        lastOfBooks=lastOfBooks->next;
    }
}

BooksCoordinator::~BooksCoordinator()
{
    Node **currentNode = &firstOfBooks;
    while(*currentNode != NULL){
        Node *toDelete = *currentNode;
        *currentNode = toDelete->next;
        delete toDelete;
        currentNode = &(*currentNode)->next;
    }
    firstOfBooks = NULL;
    delete firstOfBooks;
    lastOfBooks = NULL;
    delete lastOfBooks;
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
    Node* currentNode = firstOfBooks;
    system("cls");
    cout<<"-----KSIAZKI-----\n\n";
    if (currentNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj ksiazki."<<"\n";
    else
    {
        while(currentNode != NULL){
            showSingleBook(currentNode->book);
            currentNode = currentNode->next;
        }
    }
    currentNode = NULL;
    delete currentNode;
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
    Node* currentNode = firstOfBooks;
    int searchedID;
    bool bookExists = false;
    char searchChoice;
    string newData;

    system("cls");
    cout<<"WYSZUKAJ POZYCJE\n\n";

    if (currentNode == NULL)
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
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O ID "<<ID<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getID() == ID){
            showBookDetails(currentNode->book);
            found = true;
            break;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji o ID = "<<ID<<endl<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByName(string name)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI NAPISANE PRZEZ "<<name<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getAuthorsName() == name){
            showBookDetails(currentNode->book);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();

}

void BooksCoordinator::searchBySurname(string surname)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI NAPISANE PRZEZ "<<surname<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getAuthorsSurname() == surname){
            showBookDetails(currentNode->book);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByTitle(string title)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O TYTULE "<<title<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getTitle() == title){
            showBookDetails(currentNode->book);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByYear(int yearPublished)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI WYDANE W "<<yearPublished<<" ROKU -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getYearPublished() == yearPublished){
            showBookDetails(currentNode->book);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByGenre(string genre)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI Z GATUNKU "<<genre<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getGenre() == genre){
            showBookDetails(currentNode->book);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByISBN(string ISBN)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O NUMERZE ISBN "<<ISBN<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getISBN() == ISBN){
            showBookDetails(currentNode->book);
            found = true;
            break;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void BooksCoordinator::searchByStatus(string status)
{
    Node* currentNode = firstOfBooks;
    bool found = false;
    system("cls");
    cout<<"----- KSIAZKI O STATUSIE "<<status<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->book.getStatus() == status){
            showBookDetails(currentNode->book);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

Node* BooksCoordinator::findSpot(Book book)
{
    Node* currentNode = firstOfBooks;
    while(currentNode != NULL && currentNode->book.getAuthorsSurname() < book.getAuthorsSurname())
        currentNode=currentNode->next;
    return currentNode;
}

void BooksCoordinator::addSingleBook(Book book)
{
    Node* pom = NULL;
    Node* temp = new Node();
    temp = NULL;
    Node* newNode = new Node();
    newNode->book = book;

    if (firstOfBooks == NULL) {
        firstOfBooks = newNode;
        lastOfBooks = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    } else {
        temp = findSpot(book);
        if(firstOfBooks == temp){
            newNode->next = firstOfBooks;
            firstOfBooks->prev = newNode;
            newNode->prev = NULL;
            firstOfBooks = newNode;
        } else if (temp == NULL){
            lastOfBooks->next = newNode;
            newNode->prev = lastOfBooks;
            newNode->next = temp;
            lastOfBooks = newNode;
        } else {
            pom=temp->prev;
            pom->next=newNode;
            newNode->prev=temp->prev;
            temp->prev=newNode;
            newNode->next=temp;
        }
        temp = NULL;
        delete temp;
        pom = NULL;
        delete pom;
    }
}

bool BooksCoordinator::editBook(){
    Node* currentNode = firstOfBooks;
    int searchedID;
    bool bookExists = false;
    char choice;
    string newData;

    system("cls");
    cout<<"EDYTUJ KONTAKT\n\n";

    if (currentNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Podaj ID ksiazki do edytowania: ";
        searchedID = DataManipulation::loadInteger();

        while(currentNode != NULL)
        {
            if(currentNode->book.getID() == searchedID)
            {
                bookExists = true;
                showBookDetails(currentNode->book);

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
                    currentNode->book.setAuthorsName(DataManipulation::loadLine());
                    break;
                case '2':
                    cout<<"Podaj nowe nazwisko: ";
                    currentNode->book.setAuthorsSurname(DataManipulation::loadLine());
                    break;
                case '3':
                    cout<<"Podaj nowy tytul: ";
                    currentNode->book.setTitle(DataManipulation::loadLine());
                    break;
                case '4':
                    cout<<"Podaj nowy rok wydania: ";
                    currentNode->book.setYearPublished(DataManipulation::loadInteger());
                    break;
                case '5':
                    cout<<"Podaj nowy adres zamieszkania ";
                    currentNode->book.setISBN(DataManipulation::loadLine());
                    break;
                case '6':
                    cout<<"Podaj nowy adres zamieszkania ";
                    currentNode->book.setGenre(DataManipulation::loadLine());
                    break;
                case '7':
                    cout<<"Podaj nowy adres zamieszkania ";
                    currentNode->book.setStatus(DataManipulation::loadLine());
                    break;
                case '8':
                    break;
                }
                booksDB->editBookInFile(currentNode->book);
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

bool BooksCoordinator::removeBook(){

}
