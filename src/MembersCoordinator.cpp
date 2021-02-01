#include "MembersCoordinator.h"

MembersCoordinator::MembersCoordinator(MemberNode* firstOfMembers, MemberNode* lastOfMembers, MembersDB *membersDB)
{
    this->membersDB = membersDB;
    this->firstOfMembers = firstOfMembers;
    this->lastOfMembers = lastOfMembers;
}

MembersCoordinator::~MembersCoordinator()
{
    MemberNode **currentMemberNode = &firstOfMembers;
    while(*currentMemberNode != NULL){
        MemberNode *toDelete = *currentMemberNode;
        *currentMemberNode = toDelete->next;
        delete toDelete;
        currentMemberNode = &(*currentMemberNode)->next;
    }
    delete firstOfMembers;
    firstOfMembers = NULL;
    delete lastOfMembers;
    lastOfMembers = NULL;
}

void MembersCoordinator::showSingleMember(Member member){
    cout<<member.getID()<<" "<<
    member.getMemberName()<<" "<<
    member.getMemberSurname()<<" "<<
    member.getMemberTown()<<" "<<
    member.getMemberStreet()<<" "<<
    member.getMemberNumber()<<" "<<
    member.getMemberZIP()<<" "<<endl;
}

void MembersCoordinator::showMembersList(){
    MemberNode* currentMemberNode = firstOfMembers;
    system("cls");
    cout<<"-----CZYTELNICY-----\n\n";
    if (currentMemberNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj czlonkow."<<"\n";
    else
    {
        while(currentMemberNode != NULL){
            showSingleMember(currentMemberNode->member);
            currentMemberNode = currentMemberNode->next;
        }
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::showMemberDetails(Member member){
    cout<<"Id: "<<member.getID()<<endl;
    cout<<"Imiona: "<<member.getMemberName()<<endl;
    cout<<"Nazwisko: "<<member.getMemberSurname()<<endl;
    cout<<"Miejscowosc: "<<member.getMemberTown()<<endl;
    cout<<"Ulica: "<<member.getMemberStreet()<<endl;
    cout<<"Numer budynku: "<<member.getMemberNumber()<<endl;
    cout<<"Kod pocztowy: "<<member.getMemberZIP()<<endl;


}

Member MembersCoordinator::setMemberData(){
    Member member;
    string memberName, memberSurname, memberTown, memberStreet, memberNumber, memberZIP;
    member.setID(membersDB->getLastMemberID()+1);

    cout << "Podaj imie czytelnika: \n";
    memberName = DataManipulation::loadLine();
    member.setMemberName(memberName);

    cout << "Podaj nazwisko czytelnika: \n";
    memberSurname = DataManipulation::loadLine();
    member.setMemberSurname(memberSurname);

    cout << "Podaj miejscowosc: \n";
    memberTown = DataManipulation::loadLine();
    member.setMemberTown(memberTown);

    cout << "Podaj ulice: \n";
    memberStreet = DataManipulation::loadLine();
    member.setMemberStreet(memberStreet);

    cout << "Podaj numer budynku: \n";
    memberNumber = DataManipulation::loadLine();
    member.setMemberNumber(memberNumber);

    cout << "Podaj kod pocztowy: \n";
    memberZIP = DataManipulation::loadLine();
    member.setMemberZIP(memberZIP);

    return member;
}

void MembersCoordinator::addNewMember()
{
    Member member;
    system("cls");
    cout << "DODAJ NOWEGO CZYTELNIKA\n\n";

    member = setMemberData();

    if (membersDB->addMemberToDB(member))
    {
        addSingleMember(member);
        cout << "Pomyslnie dodano czytelnika! \n";
    }
    else
        cout << "Nie udalo sie dodac czytelnika! \n";

    cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
    getch();
}

void MembersCoordinator::searchForMember()
{
    MemberNode* currentMemberNode = firstOfMembers;
    int searchedID;
    bool memberExists = false;
    char searchChoice;
    string newData;

    system("cls");
    cout<<"WYSZUKAJ CZYTELNIKA\n\n";

    if (currentMemberNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Wybierz wg czego chcesz prowadziæ poszukiwania: \n";
        cout << "1. ID\n";
        cout << "2. Imie/Imiona\n";
        cout << "3. Nazwisko\n";
        cout << "4. Miejscowosc\n";
        cout << "5. Ulica\n";
        cout << "6. Numer budynku\n";
        cout << "7. Kod pocztowy\n";


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
        case '4':
            searchByTown(DataManipulation::loadLine());
            break;
        case '5':
            searchByStreet(DataManipulation::loadLine());
            break;
        case '6':
            searchByNumber(DataManipulation::loadLine());
            break;
        case '7':
            searchByZIP(DataManipulation::loadLine());
            break;
        }
    }
    cout<<"Kliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByID(int ID)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY O ID "<<ID<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getID() == ID){
            showMemberDetails(currentMemberNode->member);
            found = true;
            break;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji o ID = "<<ID<<endl<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByName(string name)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY O IMIENIU: "<<name<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getMemberName() == name){
            showMemberDetails(currentMemberNode->member);
            found = true;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();

}

void MembersCoordinator::searchBySurname(string surname)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY O NAZWISKU:  "<<surname<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getMemberSurname() == surname){
            showMemberDetails(currentMemberNode->member);
            found = true;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByTown(string town)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY Z MIEJSCOWOSCI:  "<<town<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getMemberTown() == town){
            showMemberDetails(currentMemberNode->member);
            found = true;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByStreet(string street)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY Z ULICY:  "<<street<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getMemberStreet() == street){
            showMemberDetails(currentMemberNode->member);
            found = true;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByNumber(string number)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY Z BUDYNKU O NR:  "<<number<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getMemberNumber() == number){
            showMemberDetails(currentMemberNode->member);
            found = true;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void MembersCoordinator::searchByZIP(string zip)
{
    MemberNode* currentMemberNode = firstOfMembers;
    bool found = false;
    system("cls");
    cout<<"----- CZYTELNICY Z KODEM POCZTOWYM:  "<<zip<<" -----\n\n";
    while(currentMemberNode != NULL){
        if(currentMemberNode->member.getMemberZIP() == zip){
            showMemberDetails(currentMemberNode->member);
            found = true;
        }
        currentMemberNode = currentMemberNode->next;
    }
    if(found == false){
        cout<<"Brak pozycji."<<endl;
    }
    currentMemberNode = NULL;
    delete currentMemberNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

MemberNode* MembersCoordinator::findSpot(Member member)
{
    MemberNode* currentMemberNode = firstOfMembers;
    while(currentMemberNode != NULL && currentMemberNode->member.getMemberSurname() < member.getMemberSurname())
        currentMemberNode=currentMemberNode->next;
    return currentMemberNode;
}

MemberNode* MembersCoordinator::getMemberNode(int Id)
{
    MemberNode* currentMemberNode = firstOfMembers;
    while(currentMemberNode != NULL && currentMemberNode->member.getID() != Id)
        currentMemberNode=currentMemberNode->next;
    return currentMemberNode;
}

void MembersCoordinator::addSingleMember(Member member)
{
    MemberNode* pom = NULL;
    MemberNode* temp = new MemberNode();
    temp = NULL;
    MemberNode* newMemberNode = new MemberNode();
    newMemberNode->member = member;

    if (firstOfMembers == NULL) {
        firstOfMembers = newMemberNode;
        lastOfMembers = newMemberNode;
        newMemberNode->prev = NULL;
        newMemberNode->next = NULL;
    } else {
        temp = findSpot(member);
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
        temp = NULL;
        delete temp;
        pom = NULL;
        delete pom;
    }
}

bool MembersCoordinator::editMember()
{
    MemberNode* currentMemberNode = firstOfMembers;
    int searchedID;
    bool memberExists = false;
    char choice;
    string newData;

    system("cls");
    cout<<"EDYTUJ DANE CZYTELNIKA\n\n";

    if (currentMemberNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Podaj ID czytelnika do edytowania: ";
        searchedID = DataManipulation::loadInteger();

        while(currentMemberNode != NULL)
        {
            if(currentMemberNode->member.getID() == searchedID)
            {
                memberExists = true;
                showMemberDetails(currentMemberNode->member);

                cout<<"Wybierz dane do zmiany: \n\n";
                cout<<"1. Imie\n";
                cout<<"2. Nazwisko\n";
                cout<<"3. Miejscowosc\n";
                cout<<"4. Ulica\n";
                cout<<"5. Numer budynku\n";
                cout<<"6. Kod pocztowy\n";

                choice = DataManipulation::loadCharacter();

                switch(choice)
                {
                case '1':
                    cout<<"Podaj nowe imie/imiona: ";
                    currentMemberNode->member.setMemberName(DataManipulation::loadLine());
                    break;
                case '2':
                    cout<<"Podaj nowe nazwisko: ";
                    currentMemberNode->member.setMemberSurname(DataManipulation::loadLine());
                    break;
                case '3':
                    cout<<"Podaj nowa miejscowosc: ";
                    currentMemberNode->member.setMemberTown(DataManipulation::loadLine());
                    break;
                case '4':
                    cout<<"Podaj nowa ulice: ";
                    currentMemberNode->member.setMemberStreet(DataManipulation::loadLine());
                    break;
                case '5':
                    cout<<"Podaj nowy numer budynku: ";
                    currentMemberNode->member.setMemberNumber(DataManipulation::loadLine());
                    break;
                case '6':
                    cout<<"Podaj nowy kod pocztowy: ";
                    currentMemberNode->member.setMemberZIP(DataManipulation::loadLine());
                    break;

                }
                membersDB->editMemberInFile(currentMemberNode->member);
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
    MemberNode* currentMemberNode = firstOfMembers;
    int searchedID;
    bool memberExists = false;
    char choice;
    string newData;

    system("cls");
    cout<<"USUN CZYTELNIKA\n\n";

    if (currentMemberNode == NULL)
    {
        cout<<"Baza pozycji jest pusta!\n";
    } else {
        cout << "Podaj ID czytelnika do usuniecia: ";
        searchedID = DataManipulation::loadInteger();

        while(currentMemberNode != NULL)
        {
            if(currentMemberNode->member.getID() == searchedID)
            {
                memberExists = true;
                showMemberDetails(currentMemberNode->member);

                cout<<"Czy na pewno chcesz usunac czytelnika?\n"
                "Potwierdz usuniecie klawiszem t. Zrezygnuj klawiszem n.\n";

                choice = DataManipulation::loadCharacter();
                if (choice == 't')
                {
                    deleteMember(currentMemberNode);
                    membersDB->removeMemberFromDB(searchedID);
                    break;
                }
                else if (choice == 'n')
                    break;
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

void MembersCoordinator::deleteMember(MemberNode* node){
    MemberNode *tmp = NULL;
    if(firstOfMembers == NULL)
        return;
    if(node == firstOfMembers){
        firstOfMembers = firstOfMembers->next;
        if(firstOfMembers != NULL)
            firstOfMembers->prev = NULL;
    } else {
        if(node == lastOfMembers){
            lastOfMembers = lastOfMembers->prev;
            if(lastOfMembers != NULL)
                lastOfMembers->next = NULL;
        } else {
            tmp = node->prev;
            tmp->next = tmp->next;
            tmp = node->next;
            tmp->prev = node->prev;
        }
    }
    delete node;
    node = NULL;
    return;
}
