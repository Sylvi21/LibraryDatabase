#ifndef MEMBERSSCOORDINATOR_H
#define MEMBERSSCOORDINATOR_H
#include "MembersStruct.h"
#include "Member.h"
#include "MemberDB.h"
#include "DataManipulation.h"
#include <conio.h>

using namespace std;

class MembersCoordinator
{
    private:
        MembersDB *membersDB;
        MemberNode* firstOfMembers;
        MemberNode* lastOfMembers;

        void addSingleMember(Member member);
        void searchByID(int ID);
        void searchByName(string name);
        void searchBySurname(string surname);
        void searchByTown(string town);
        void searchByStreet(string street);
        void searchByNumber(string number);
        void searchByZIP(string zip);
        void showSingleMember(Member member);
        void showMemberDetails(Member member);
        void deleteMember(MemberNode* node);

    public:
        MembersCoordinator(MemberNode* firstOfMembers, MemberNode* lastOfMembers, MembersDB *membersDB);
        virtual ~MembersCoordinator();
        void showMembersList();
        void addNewMember();
        Member getSingleMember(int memberId);
        Member setMemberData();
        MemberNode* findSpot(Member member);
        MemberNode* getMemberNode(int Id);
        void searchForMember();
        bool editMember();
        bool removeMember();
};

#endif // MEMBERSSCOORDINATOR_H
