#include "MemberDB.h"

MembersDB::MembersDB()
{

}

MembersDB::~MembersDB()
{

}

MemberNode* MembersDB::getFront()
{
    return firstOfMembers;
}

MemberNode* MembersDB::getBack()
{
    return lastOfMembers;
}

int MembersDB::getLastMemberID(){
    return lastMemberID;
}

int MembersDB::setLastMemberID(string dataLine)
{
    int newID = DataManipulation::extractNumber(dataLine, 1);
    lastMemberID = newID;
    return lastMemberID;
}

string MembersDB::getFilename(){
    return membersFileName;
}

bool MembersDB::addMemberToDB(Member member)
{
    fstream membersDB;
    membersDB.open(getFilename(), ios::app);
    if (membersDB.good() == true)
    {
        membersDB<<member.getID()<<"|";
        membersDB<<member.getMemberName()<<"|";
        membersDB<<member.getMemberSurname()<<"|";


        membersDB.close();
        lastMemberID++;
        return true;
    }
    else
    {
        cout<<"Nie udalo sie otworzyc pliku i zapisac do niego danych. ";
        return false;
    }
}

Member MembersDB::getSingleMemberFromFile(string dataLine, int lastMemberID)
{
    Member singleMember;
    string subLine="";
    int lineLength=dataLine.length();
    int subLineNumber=1;
    for(int i=0; i<lineLength; i++)
    {
        if(dataLine[i] != '|')
        {
            subLine+=dataLine[i];
        }
        else
        {
            switch(subLineNumber)
            {
            case 7:
                singleMember.setID(stoi(subLine.c_str()));
                break;
            case 8:
                singleMember.setMemberName(subLine);
                break;
            case 9:
                singleMember.setMemberSurname(subLine);
                break;
            }
            subLine="";
            subLineNumber++;
        }
    }
    return singleMember;
}


MemberNode* MembersDB::findSpot(MemberNode* members, Member member)
{
    while(members != NULL && members->member.getMemberSurname() < member.getMemberSurname())
        members=members->next;
    return members;
}

MemberNode* MembersDB::loadMembersFromFile(){
    string dataLine="", lastMemberDataLine="";
    MemberNode* firstOfMembers = NULL;
    MemberNode* lastOfMembers = NULL;
    MemberNode* pom = NULL;
    MemberNode* temp = new MemberNode();
    temp = NULL;
    Member singleMember;
    fstream membersFile;
    membersFile.open("Members.txt", ios::in);

    if (membersFile.good() == true)
    {
        while (getline(membersFile, dataLine))
        {
            singleMember = getSingleMemberFromFile(dataLine, lastMemberID);
            MemberNode* newMemberNode = new MemberNode();
            newMemberNode->member = singleMember;
            if (firstOfMembers == NULL) {
                firstOfMembers = newMemberNode;
                lastOfMembers = newMemberNode;
                newMemberNode->prev = NULL;
                newMemberNode->next = NULL;
            } else {
                temp = findSpot(firstOfMembers, singleMember);
                if(firstOfMembers == temp){
                    newMemberNode->next = firstOfMembers;
                    firstOfMembers->prev = newMemberNode;
                    newMemberNode->prev = NULL;
                    firstOfMembers = newMemberNode;
                } else if (temp == NULL){
                    lastOfMembers->next = newMemberNode;
                    newMemberNode->prev = lastOfMembers;
                    newMemberNode->next = temp;
                    lastOfMembers = newMemberNode;
                } else {
                    pom=temp->prev;
                    pom->next=newMemberNode;
                    newMemberNode->prev=temp->prev;
                    temp->prev=newMemberNode;
                    newMemberNode->next=temp;
                }
            }
            lastMemberDataLine = dataLine;
        }
        membersFile.close();
    }
    if (lastMemberDataLine != "")
    {
        this->lastMemberID = setLastMemberID(lastMemberDataLine);
    }
    temp = NULL;
    delete temp;
    pom = NULL;
    delete pom;

    return firstOfMembers;
}

void MembersDB::editMemberInFile(Member memberToEdit){
    string line=""; string subLine="";
    ifstream inFile("Members.txt");
    ofstream outFile;
    outFile.open("temp.txt");
    if(!inFile.good())
    {
        outFile.close();
        remove("temp.txt");
        cout<<"Nie udalo sie otworzyc pliku z czlonkami biblioteki.\n";
    }
    else
    {
        while (getline(inFile, line))
        {
            subLine="";
            int i=0;
            while(line[i]!='|')
            {
                subLine+=line[i];
                i++;
            }
            if (atoi(subLine.c_str()) == memberToEdit.getID())
            {
                outFile<<memberToEdit.getID()<<"|";
                outFile<<memberToEdit.getMemberName()<<"|";
                outFile<<memberToEdit.getMemberSurname()<<"|";

            }
            else outFile<<line<<endl;
        }
        outFile.close();
        inFile.close();
        remove("Members.txt");
        rename("temp.txt", "Members.txt");
        cout<<"Lista czlonkow edytowana pomyslnie!\n";
    }
}
