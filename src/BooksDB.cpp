#include "BooksDB.h"

BooksDB::BooksDB()
{

}

BooksDB::~BooksDB()
{
    //dtor
}

int BooksDB::getLastBookID(){
    return lastBookID;
}

int BooksDB::setLastBookID(string dataLine)
{
    int newID = DataManipulation::extractNumber(dataLine, 1);
    lastBookID = newID;
    return lastBookID;
}

string BooksDB::getFilename(){
    return booksFileName;
}

bool BooksDB::addBookToDB(Book book)
{
    fstream booksDB;
    booksDB.open(getFilename(), ios::app);
    if (booksDB.good() == true)
    {
        booksDB<<book.getID()<<"|";
        booksDB<<book.getAuthorsName()<<"|";
        booksDB<<book.getAuthorsSurname()<<"|";
        booksDB<<book.getTitle()<<"|";
        booksDB<<book.getYearPublished()<<"|";
        booksDB<<book.getGenre()<<"|";
        booksDB<<book.getISBN()<<"|";
        booksDB<<book.getStatus()<<"|"<<endl;

        booksDB.close();
        lastBookID++;
        return true;
    }
    else
    {
        cout<<"Nie udalo sie otworzyc pliku i zapisac do niego danych. ";
        return false;
    }
}

Book BooksDB::getSingleBookFromFile(string dataLine, int lastBookID)
{
    Book singleBook;
    string subLine="";
    int lineLength=dataLine.length();
    int subLineNumber=1;
    for(int i=0; i<lineLength; i++)
    {
        if(dataLine[i] != '|')
        {
            subLine+=dataLine[i];
        }
        else
        {
            switch(subLineNumber)
            {
            case 1:
                singleBook.setID(stoi(subLine.c_str()));
                break;
            case 2:
                singleBook.setAuthorsName(subLine);
                break;
            case 3:
                singleBook.setAuthorsSurname(subLine);
                break;
            case 4:
               singleBook.setTitle(subLine);
                break;
            case 5:
                singleBook.setYearPublished(stoi(subLine.c_str()));
                break;
            case 6:
                singleBook.setGenre(subLine);
                break;
            case 7:
                singleBook.setISBN(subLine);
                break;
            case 8:
                singleBook.setStatus(subLine);
                break;
            }
            subLine="";
            subLineNumber++;
        }
    }
    return singleBook;
}
/*
Node* BooksDB::findSpot(Node* lol, Book book)
{
    Node* books = lol;
    while(books != NULL && books->book.getAuthorsSurname() < book.getAuthorsSurname()){
        if(books->next == NULL)
            break;
        books=books->next;
    }
    return books;
}*/

Node* BooksDB::findSpot(Node* books, Book book)
{
    while(books != NULL && books->book.getAuthorsSurname() < book.getAuthorsSurname())
        books=books->next;
    return books;
}

Node* BooksDB::loadBooksFromFile(){
    string dataLine="", lastBookDataLine="";
    Node* firstOfBooks = NULL;
    Node* lastOfBooks = NULL;
    Node* pom = NULL;
    Node* temp = new Node();
    temp = NULL;
    Book singleBook;
    fstream booksFile;
    booksFile.open("Books.txt", ios::in);

    if (booksFile.good() == true)
    {
        while (getline(booksFile, dataLine))
        {
            singleBook = getSingleBookFromFile(dataLine, lastBookID);
            Node* newNode = new Node();
            newNode->book = singleBook;
            if (firstOfBooks == NULL) {
                firstOfBooks = newNode;
                lastOfBooks = newNode;
                newNode->prev = NULL;
                newNode->next = NULL;
            } else {
                temp = findSpot(firstOfBooks, singleBook);
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
            }
            lastBookDataLine = dataLine;
        }
        booksFile.close();
    }
    if (lastBookDataLine != "")
    {
        this->lastBookID = setLastBookID(lastBookDataLine);
    }
    temp = NULL;
    delete temp;
    pom = NULL;
    delete pom;

    return firstOfBooks;
}

void BooksDB::editBookInFile(Book bookToEdit){
    string line=""; string subLine="";
    ifstream inFile("Books.txt");
    ofstream outFile;
    outFile.open("temp.txt");
    if(!inFile.good())
    {
        outFile.close();
        remove("temp.txt");
        cout<<"Nie udalo sie otworzyc pliku z kontaktami.\n";
    }
    else
    {
        while (getline(inFile, line))
        {
            subLine="";
            int i=0;
            while(line[i]!='|')
            {
                subLine+=line[i];
                i++;
            }
            if (atoi(subLine.c_str()) == bookToEdit.getID())
            {
                outFile<<bookToEdit.getID()<<"|";
                outFile<<bookToEdit.getAuthorsName()<<"|";
                outFile<<bookToEdit.getAuthorsSurname()<<"|";
                outFile<<bookToEdit.getTitle()<<"|";
                outFile<<bookToEdit.getYearPublished()<<"|";
                outFile<<bookToEdit.getGenre()<<"|";
                outFile<<bookToEdit.getISBN()<<"|";
                outFile<<bookToEdit.getStatus()<<"|"<<endl;
            }
            else outFile<<line<<endl;
        }
        outFile.close();
        inFile.close();
        remove("Books.txt");
        rename("temp.txt", "Books.txt");
        cout<<"Kontakt edytowany pomyslnie!\n";
    }
}
