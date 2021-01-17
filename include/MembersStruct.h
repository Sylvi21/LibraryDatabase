#ifndef MEMBERSSTRUCT_H
#define MEMBERSSTRUCT_H
#include "Member.h"

struct MemberNode {
    Member member;
    MemberNode *prev;
    MemberNode *next;
};

#endif // MEMBERSSTRUCT_H
