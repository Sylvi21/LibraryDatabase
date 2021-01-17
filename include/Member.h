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
    public:
        Member();
        virtual ~Member();
        int getID();
        void setID(int memberID);
        string getMembersName();
        void setMemberName(string memberName);
        string getMemberSurname();
        void setMemberSurname(string memberSurname);
};

#endif // MEMBER_H
