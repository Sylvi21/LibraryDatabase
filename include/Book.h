#ifndef BOOK_H
#define BOOK_H
#include <string>

using namespace std;

class Book
{
    private:
        int bookID;
        string authorsName;
        string authorsSurname;
        string title;
        int yearPublished;
        string genre;
        string status;
        string ISBN;
    public:
        Book();
        virtual ~Book();
        int getID();
        void setID(int bookID);
        string getAuthorsName();
        void setAuthorsName(string authorsName);
        string getAuthorsSurname();
        void setAuthorsSurname(string authorsSurname);
        string getTitle();
        void setTitle(string title);
        int getYearPublished();
        void setYearPublished(int yearPublished);
        string getISBN();
        void setISBN(string ISBN);
        string getGenre();
        void setGenre(string genre);
        string getStatus();
        void setStatus(string status);
};

#endif // BOOK_H
