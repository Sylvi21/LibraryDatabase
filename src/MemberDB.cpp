#include "MemberDB.h"

MembersDB::MembersDB()
{
}

MembersDB::~MembersDB()
{
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
                singleMember.setAuthorsName(subLine);
                break;
            case 9:
                singleMember.setAuthorsSurname(subLine);
                break;
            }
            subLine="";
            subLineNumber++;
        }
    }
    return singleMember;
}


Node* MembersDB::findSpot(Node* members, Member member)
{
    while(members != NULL && members->member.getMemberSurname() < member.getMemberSurname())
        members=members->next;
    return members;
}

Node* MembersDB::loadMembersFromFile(){
    string dataLine="", lastBookDataLine="";
    Node* firstOfMembers = NULL;
    Node* lastOfMembers = NULL;
    Node* pom = NULL;
    Node* temp = new Node();
    temp = NULL;
    Member singleMember;
    fstream membersFile;
    membersFile.open("Members.txt", ios::in);

    if (memberssFile.good() == true)
    {
        while (getline(membersFile, dataLine))
        {
            singleMember = getSingleMemberFromFile(dataLine, lastMemberID);
            Node* newNode = new Node();
            newNode->member = singleMember;
            if (firstOfMembers == NULL) {
                firstOfMembers = newNode;
                lastOfMembers = newNode;
                newNode->prev = NULL;
                newNode->next = NULL;
            } else {
                temp = findSpot(firstOfMembers, singleMember);
                if(firstOfMemberss == temp){
                    newNode->next = firstOfMembers;
                    firstOfMembers->prev = newNode;
                    newNode->prev = NULL;
                    firstOfMembers = newNode;
                } else if (temp == NULL){
                    lastOfMembers->next = newNode;
                    newNode->prev = lastOfMembers;
                    newNode->next = temp;
                    lastOfMembers = newNode;
                } else {
                    pom=temp->prev;
                    pom->next=newNode;
                    newNode->prev=temp->prev;
                    temp->prev=newNode;
                    newNode->next=temp;
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
