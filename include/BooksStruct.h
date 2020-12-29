#ifndef BOOKSSTRUCT_H
#define BOOKSSTRUCT_H

struct Node {
    Book book;
    Node *prev;
    Node *next;
};

#endif // BOOKSSTRUCT_H
