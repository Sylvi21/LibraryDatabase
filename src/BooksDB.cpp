#include "BooksDB.h"

BooksDB::BooksDB()
{
    this->firstOfBooks = NULL;
    this->lastOfBooks = NULL;
    this->lastBookID = 0;
}

BooksDB::~BooksDB()
{

}

BookNode* BooksDB::getFront()
{
    return firstOfBooks;
}

BookNode* BooksDB::getBack()
{
    return lastOfBooks;
}

int BooksDB::getLastBookID()
{
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

BookNode* BooksDB::findSpot(BookNode* books, Book book)
{
    while(books != NULL && books->book.getAuthorsSurname() < book.getAuthorsSurname())
        books=books->next;
    return books;
}

void BooksDB::loadBooksFromFile(){
    string dataLine="", lastBookDataLine="";
    BookNode* pom = NULL;
    BookNode* temp = new BookNode();
    temp = NULL;
    Book singleBook;
    fstream booksFile;
    booksFile.open("Books.txt", ios::in);

    if (booksFile.good() == true)
    {
        while (getline(booksFile, dataLine))
        {
            singleBook = getSingleBookFromFile(dataLine, lastBookID);
            BookNode* newBookNode = new BookNode();
            newBookNode->book = singleBook;
            if (firstOfBooks == NULL) {
                firstOfBooks = newBookNode;
                lastOfBooks = newBookNode;
                newBookNode->prev = NULL;
                newBookNode->next = NULL;
            } else {
                temp = findSpot(firstOfBooks, singleBook);
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
            }
            lastBookDataLine = dataLine;
        }
        booksFile.close();
    }
    if (lastBookDataLine != "")
    {
        this->lastBookID = setLastBookID(lastBookDataLine);
    }
    delete temp;
    temp = NULL;
    delete pom;
    pom = NULL;
    cout<<"firstbook:"<<firstOfBooks->book.getID()<<endl<<endl;
}

bool BooksDB::editBookInDB(Book book){
    string line=""; string subLine="";
    ifstream inFile("Books.txt");
    ofstream outFile;
    outFile.open("temp.txt");
    if(!inFile.good())
    {
        outFile.close();
        remove("temp.txt");
        cout<<"Nie udalo sie otworzyc pliku z ksiazkami.\n";
        return false;
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
            if (atoi(subLine.c_str()) == book.getID())
            {
                outFile<<book.getID()<<"|";
                outFile<<book.getAuthorsName()<<"|";
                outFile<<book.getAuthorsSurname()<<"|";
                outFile<<book.getTitle()<<"|";
                outFile<<book.getYearPublished()<<"|";
                outFile<<book.getGenre()<<"|";
                outFile<<book.getISBN()<<"|";
                outFile<<book.getStatus()<<"|"<<endl;
            }
            else outFile<<line<<endl;
        }
        outFile.close();
        inFile.close();
        remove("Books.txt");
        rename("temp.txt", "Books.txt");
        cout<<"Ksiazka edytowana pomyslnie!\n";
        return true;
    }
}

void BooksDB::removeBookFromDB(int ID){
    ifstream inFile("Books.txt");
    ofstream outFile;
    outFile.open("temp.txt", ios::out | ios::app);

    string line="";
    string subLine;
    if(inFile.good())
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
            if(atoi(subLine.c_str()) == ID)
                continue;
            else
            {
                outFile<<line<<endl;
                lastBookID = atoi(subLine.c_str());
            }
        }
        outFile.close();
        inFile.close();
        remove("Books.txt");
        rename("temp.txt", "Books.txt");
        cout<<"Ksiazka usunieta pomyslnie!\n";
    }
    else
    {
        cout<<"Program napotkal blad. Nie mozna otworzyc pliku.";
        outFile.close();
        remove("temp.txt");
    }
}
