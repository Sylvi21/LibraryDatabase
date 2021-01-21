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
        MemberNode* firstOfMembers;
        MemberNode* lastOfMembers;
    public:
        MembersDB();
        virtual ~MembersDB();
        MemberNode* getFront();
        MemberNode* getBack();
        MemberNode* loadMembersFromFile();
        MemberNode* findSpot(MemberNode* members, Member member);
        int getLastMemberID();
        int setLastMemberID(string dataLine);
        string getFilename();
        bool addMemberToDB(Member member);
        Member getSingleMemberFromFile(string dataLine, int lastMemberID);
        void editMemberInFile(Member member);
        void removeMemberFromDB(int ID);

};

#endif // MEMBERDB_H
