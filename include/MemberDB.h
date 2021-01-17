#ifndef MEMBERDB_H
#define MEMBERDB_H
#include "Member.h"
#include "DataManipulation.h"
#include "MembersStruct.h"
#include <iostream>
#include <fstream>

using namespace std;

class MembersDB
{
    private:
        string membersFileName = "Members.txt";
        int lastMemberID;
    public:
        MembersDB();
        virtual ~MembersDB();
        MemberNode* loadMembersFromFile();
        MemberNode* findSpot(MemberNode* members, Member member);
        int getLastMemberID();
        int setLastMemberID(string dataLine);
        string getFilename();
        bool addMemberToDB(Member member);
        Member getSingleMemberFromFile(string dataLine, int lastMemberID);
        void editMemberInFile(Member member);
};

#endif // MEMBERDB_H
