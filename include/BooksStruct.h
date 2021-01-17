#ifndef BOOKSSTRUCT_H
#define BOOKSSTRUCT_H
#include "Book.h"

struct BookNode {
    Book book;
    BookNode *prev;
    BookNode *next;
};

#endif // BOOKSSTRUCT_H
