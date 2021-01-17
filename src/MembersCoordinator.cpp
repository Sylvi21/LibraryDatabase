#include "MembersCoordinator.h"

MembersCoordinator::MembersCoordinator(MembersDB *membersDB)
{
    this->membersDB = membersDB;
    this->firstOfMembers = membersDB->loadMembersFromFile();
    this->lastOfMembers = firstOfMembers;
    while(lastOfMembers != NULL){
        if(lastOfMembers->next == NULL)
            break;
        lastOfMembers=lastOfMembers->next;
    }
}

MembersCoordinator::~MembersCoordinator()
{
    Node **currentNode = &firstOfMembers;
    while(*currentNode != NULL){
        Node *toDelete = *currentNode;
        *currentNode = toDelete->next;
        delete toDelete;
        currentNode = &(*currentNode)->next;
    }
    firstOfMembers = NULL;
    delete firstOfMembers;
    lastOfMembers = NULL;
    delete lastOfMembers;
}

void MembersCoordinator::showSingleMember(Member member){
    cout<<member.getID()<<" "<<
    member.getMemberName()<<" "<<
    member.getMemberSurname()<<endl;
}

void MembersCoordinator::showMembersList(){
    Node* currentNode = firstOfMembers;
    system("cls");
    cout<<"-----CZLONKOWIE-----\n\n";
    if (currentNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj czlonkow."<<"\n";
    else
    {
        while(currentNode != NULL){
            showSingleMember(currentNode->member);
            currentNode = currentNode->next;
        }
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::showMemberDetails(Member member){
    cout<<"Id: "<<member.getID()<<endl;
    cout<<"Imiona: "<<member.getMemberName()<<endl;
    cout<<"Nazwisko: "<<member.getMemberSurname()<<endl;
}

Member MembersCoordinator::setMemberData(){
    Member member;
    string memberName, memberSurname;
    member.setID(membersDB->getLastMemberID()+1);

    cout << "Podaj imie czlonka: \n";
    memberName = DataManipulation::loadLine();
    member.setMemberName(memberName);

    cout << "Podaj nazwisko czlonka: \n";
    memberSurname = DataManipulation::loadLine();
    member.setmemberSurname(memberSurname);

    return member;
}

void MembersCoordinator::addNewMember()
{
    Member member;
    system("cls");
    cout << "DODAJ NOWEGO CZLONKA\n\n";

    member = setMemberData();

    if (membersDB->addMemberToDB(member))
    {
        addSingleMember(member);
        cout << "Pomyslnie dodano czlonka! \n";
    }
    else
        cout << "Nie udalo sie dodac czlonka! \n";

    cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
    getch();
}

void MembersCoordinator::searchForMember()
{
    Node* currentNode = firstOfMembers;
    int searchedID;
    bool memberExists = false;
    char searchChoice;
    string newData;

    system("cls");
    cout<<"WYSZUKAJ CZLONKA\n\n";

    if (currentNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Wybierz wg czego chcesz prowadziæ poszukiwania: \n";
        cout << "1. ID\n";
        cout << "2. Imie/Imiona\n";
        cout << "3. Nazwisko\n";

        searchChoice = DataManipulation::loadCharacter();

        switch(searchChoice)
        {
        case '1':
            searchByID(DataManipulation::loadInteger());
            break;
        case '2':
            searchByName(DataManipulation::loadLine());
            break;
        case '3':
            searchBySurname(DataManipulation::loadLine());
            break;
        }
    }
    cout<<"Kliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByID(int ID)
{
    Node* currentNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZLONKOWIE O ID "<<ID<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->member.getID() == ID){
            showMemberDetails(currentNode->member);
            found = true;
            break;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji o ID = "<<ID<<endl<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByName(string name)
{
    Node* currentNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZLONKOWIE O IMIENIU: "<<name<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->member.getMemberName() == name){
            showMemberDetails(currentNode->member);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();

}

void MembersCoordinator::searchBySurname(string surname)
{
    Node* currentNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZLONKOWIE O NAZWISKU:  "<<surname<<" -----\n\n";
    while(currentNode != NULL){
        if(currentNode->member.getMemberSurname() == surname){
            showMemberDetails(currentNode->member);
            found = true;
        }
        currentNode = currentNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentNode = NULL;
    delete currentNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

Node* MembersCoordinator::findSpot(Member member)
{
    Node* currentNode = firstOfMembers;
    while(currentNode != NULL && currentNode->member.getMemberSurname() < member.getMemberSurname())
        currentNode=currentNode->next;
    return currentNode;
}

void MembersCoordinator::addSingleMember(Member member)
{
    Node* pom = NULL;
    Node* temp = new Node();
    temp = NULL;
    Node* newNode = new Node();
    newNode->member = member;

    if (firstOfMembers == NULL) {
        firstOfMembers = newNode;
        lastOfMembers = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    } else {
        temp = findSpot(member);
        if(firstOfMembers == temp){
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
        temp = NULL;
        delete temp;
        pom = NULL;
        delete pom;
    }
}

bool MembersCoordinator::editMember(){
    Node* currentNode = firstOfMembers;
    int searchedID;
    bool memberExists = false;
    char choice;
    string newData;

    system("cls");
    cout<<"EDYTUJ DANE CZLONKA\n\n";

    if (currentNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Podaj ID czlonka do edytowania: ";
        searchedID = DataManipulation::loadInteger();

        while(currentNode != NULL)
        {
            if(currentNode->member.getID() == searchedID)
            {
                memberExists = true;
                showMemberDetails(currentNode->member);

                cout<<"Wybierz dane do zmiany: \n\n";
                cout<<"1. Imie\n";
                cout<<"2. Nazwisko\n";

                choice = DataManipulation::loadCharacter();

                switch(choice)
                {
                case '1':
                    cout<<"Podaj nowe imie/imiona: ";
                    currentNode->member.setMemberName(DataManipulation::loadLine());
                    break;
                case '2':
                    cout<<"Podaj nowe nazwisko: ";
                    currentNode->member.setMemberSurname(DataManipulation::loadLine());
                    break;

                }
                membersDB->editMemberInFile(currentNode->member);
                break;
            }
        }
        if (memberExists == false)
        {
            cout<<"Brak pozycji w bazie danych. Dodaj pozycje.\n";
        }
    }
    cout<<"Kliknij dowolny klawisz, aby powrocic.\n";
    getch();
}

bool MembersCoordinator::removeMember(){

}
