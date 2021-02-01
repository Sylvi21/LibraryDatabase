#ifndef MEMBER_H
#define MEMBER_H
#include <string>

using namespace std;

class Member
{
    private:
        int memberID;
        string memberName;
        string memberSurname;
        string memberTown;
        string memberStreet;
        string memberNumber;
        string memberZIP;
    public:
        Member();
        virtual ~Member();
        int getID();
        void setID(int memberID);
        string getMemberName();
        void setMemberName(string memberName);
        string getMemberSurname();
        void setMemberSurname(string memberSurname);
        string getMemberTown();
        void setMemberTown(string memberTown);
        string getMemberStreet();
        void setMemberStreet(string memberStreet);
        string getMemberNumber();
        void setMemberNumber(string memberNumber);
        string getMemberZIP();
        void setMemberZIP(string memberZIP);
};

#endif // MEMBER_H
