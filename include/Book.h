#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book
{
    private:
        int id;
        std::string authorsName;
        std::string authorsSurname;
        std::string title;
        std::string yearPublished;
        std::string genre;
        bool wypozyczona/dostepna/zaginiona;
    public:
        Book();
        virtual ~Book();
        int getID();
        void setID(int id);
        std::string getAuthorsName();
        void setAuthorsName(std::string authorsName);
        std::string getAuthorsSurname();
        void setAuthorsSurname(std::string authorsSurname);
        std::string getTitle();
        void setTitle(std::string title);
        std::string getYearPublished();
        void setYearPublished(std::string yearPublished);
        std::string getGenre();
        void setGenre(std::string genre);
};

#endif // BOOK_H
