#ifndef MEMBERSSCOORDINATOR_H
#define MEMBERSSCOORDINATOR_H
#include "Member.h"
#include "MembersDB.h"
#include "DataManipulation.h"
#include <conio.h>
#include "MembersStruct.h"

using namespace std;

class MembersCoordinator
{
    private:
        MembersDB *membersDB;
        Node* firstOfMembers;
        Node* lastOfMemberss;

        void addSingleMember(Member member);
        void searchByID(int ID);
        void searchByName(string name);
        void searchBySurname(string surname);
        void showSingleMember(Member member);
        void showMemberDetails(Member member);
    public:
        MembersCoordinator(MembersDB *membersDB);
        virtual ~MembersCoordinator();
        void showMembersList();
        void addNewMember();
        Member getSingleMember(int memberId);
        Member setMemberData();
        Node* findSpot(Member member);
        void searchForMember();
        bool editMember();
        bool removeMember();
};

#endif // MEMBERSSCOORDINATOR_H
