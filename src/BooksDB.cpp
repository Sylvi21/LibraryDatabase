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
                singleBook.setYearPublished(subLine);
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

Node* BooksDB::findSpot(Node* books, Book book)
{
    while(books != NULL && books->book.getAuthorsSurname() < book.getAuthorsSurname())
        books=books->next;
    return books;
}

Node* BooksDB::loadBooksFromFile(){
    string dataLine="", lastBookDataLine="";
    Node* books = new Node();
    books = NULL;
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
            Node* node = new Node();
            if (books == NULL) {
                books = node;
                node->book = singleBook;
                node->prev = NULL;
                node->next = NULL;
            } else {
                temp = findSpot(books, singleBook);
                if(books == temp){
                    books->prev = node;
                    node->next = books;
                    node->prev = NULL;
                    books = node;
                } else if (temp->next != NULL){
                    node->next = books->next;
                    books->next = node;
                } else {
                    books->next = node;
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

    return books;
}
