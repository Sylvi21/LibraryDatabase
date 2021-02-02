#include "TransactionsCoordinator.h"
#include "DataManipulation.h"

#include <iomanip>

TransactionsCoordinator::TransactionsCoordinator(TransactionNode* firstOfTransactions, TransactionNode* lastOfTransactions, TransactionsDB *transactionsDB)
{
    this->transactionsDB = transactionsDB;
    this->firstOfTransactions = firstOfTransactions;
    this->lastOfTransactions = lastOfTransactions;
}

TransactionsCoordinator::~TransactionsCoordinator()
{
    TransactionNode **currentTransactionNode = &firstOfTransactions;
    while(*currentTransactionNode != NULL){
        TransactionNode *toDelete = *currentTransactionNode;
        *currentTransactionNode = toDelete->next;
        delete toDelete;
        currentTransactionNode = &(*currentTransactionNode)->next;
    }
    delete firstOfTransactions;
    firstOfTransactions = NULL;
    delete lastOfTransactions;
    lastOfTransactions = NULL;
}

void TransactionsCoordinator::aquireObjectsByID(MemberNode *frontMemberNode, BookNode *frontBookNode){
    int ID, counter = 1;
    TransactionNode* currentNode = firstOfTransactions;
    while(currentNode != NULL){
        //get Member
        ID = currentNode->transaction.getMemberID();
        MemberNode *tempMember = frontMemberNode;
        while(tempMember != NULL || tempMember->member.getID()!= ID){
            if(tempMember->member.getID()== ID)
                break;
            tempMember = tempMember->next;
        }
        currentNode->member = &(tempMember->member);
        //get Book
        ID = currentNode->transaction.getBookID();
        BookNode *tempBook = frontBookNode;
        while(tempBook != NULL || tempBook->book.getID() != ID){
            if(tempBook->book.getID() == ID)
                break;
            tempBook = tempBook->next;
        }
        currentNode->book = &(tempBook->book);
        //next transaction

        if(counter == 1)
            firstOfTransactions = currentNode;
        counter ++;
        currentNode=currentNode->next;
    }

}

TransactionNode* TransactionsCoordinator::getTransactionById(int id)
{
    TransactionNode* currentNode = firstOfTransactions;
    while(currentNode != NULL){
        if(currentNode->transaction.getID() == id)
            break;
        currentNode=currentNode->next;
    }
    return currentNode;
}

TransactionNode* TransactionsCoordinator::findSpot(TransactionNode transaction)
{
    TransactionNode* currentNode = firstOfTransactions;
    while(currentNode != NULL && currentNode->transaction.getID() < transaction.transaction.getID())
        currentNode=currentNode->next;
    return currentNode;
}

void TransactionsCoordinator::addSingleTransaction(TransactionNode *transaction)
{
    TransactionNode* pom = NULL;
    TransactionNode* temp = NULL;

    if (firstOfTransactions == NULL) {
        firstOfTransactions = transaction;
        lastOfTransactions = transaction;
        transaction->prev = NULL;
        transaction->next = NULL;
    } else {
        temp = findSpot(*transaction);
        if(firstOfTransactions == temp){
            transaction->next = firstOfTransactions;
            firstOfTransactions->prev = transaction;
            transaction->prev = NULL;
            firstOfTransactions = transaction;
        } else if (temp == NULL){
            lastOfTransactions->next = transaction;
            transaction->prev = lastOfTransactions;
            transaction->next = temp;
            lastOfTransactions = transaction;
        } else {
            pom=temp->prev;
            pom->next=transaction;
            transaction->prev=temp->prev;
            temp->prev=transaction;
            transaction->next=temp;
        }
        temp = NULL;
        delete temp;
        pom = NULL;
        delete pom;
    }
}

void TransactionsCoordinator::lendBook(Member *member, Book *book)
{
    system("cls");
    cout << "WYPOZYCZ KSIAZKE\n\n";

    string date = "", dueDate = "";

    TransactionNode* transactionNode = new TransactionNode();
    transactionNode->member = member;
    transactionNode->book = book;
    transactionNode->transaction.setID(transactionsDB->getLastTransactionID()+1);
    transactionNode->transaction.setMemberID(member->getID());
    transactionNode->transaction.setBookID(book->getID());
    date = DataManipulation::getCurrentDate();
    transactionNode->transaction.setDateBorrowed(date);
    dueDate = DataManipulation::getDueDate();
    transactionNode->transaction.setDueDate(dueDate);

    if (transactionsDB->addTransactionToDB(transactionNode->transaction))
    {
        addSingleTransaction(transactionNode);
        book->setStatus("wypozyczona");
        cout << "Pomyslnie zarejestrowano wypozyczenie! \n";
    }
    else
        cout << "Nie udalo sie zarejestrowac wypozyczenia! \n";

    cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
    getch();
}

Book* TransactionsCoordinator::registerReturn(int id)
{
    int removedId; Book* book = NULL;
    TransactionNode *transactionNode = getTransactionById(id);
    if(transactionNode == NULL){
        cout << "Nie udalo sie odnalezc wypozyczenia o ID "<<id<<"! \n";
    }
    cout<<transactionNode->transaction.getID()<<endl;
    if(transactionsDB->removeTransactionFromDB(transactionNode->transaction.getID())){
        book = transactionNode->book;
        removedId = removeTransaction(transactionNode);
        if(removedId != 0){
            cout << "Zarejestrowano zwrot.\n";
        } else {
            book = NULL;
            cout << "Wystapil blad w programie. Nie udalo sie zarejestrowac zwrotu.\n";
        }
    } else {
        cout << "Wystapil blad z dostepem do bazy danych. Nie udalo sie zarejestrowac zwrotu.\n";
    }
    cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
    getch();
    return book;
}

int TransactionsCoordinator::removeTransaction(TransactionNode* node){
    TransactionNode *tmp = NULL;
    if(firstOfTransactions == NULL)
        return 0;
    int id = node->book->getID();

    if(node == firstOfTransactions){
        firstOfTransactions = firstOfTransactions->next;
        if(firstOfTransactions != NULL)
            firstOfTransactions->prev = NULL;
    } else {
        if(node == lastOfTransactions){
            lastOfTransactions = lastOfTransactions->prev;
            if(lastOfTransactions != NULL)
                lastOfTransactions->next = NULL;
        } else {
            tmp = node->prev;
            tmp->next = tmp->next;
            tmp = node->next;
            tmp->prev = node->prev;
        }
    }
    delete node;
    node = NULL;
    return id;
}

void TransactionsCoordinator::showSingleTransaction(TransactionNode* transaction)
{
    cout <<transaction->transaction.getID()<<"|"<<
    transaction->transaction.getDateBorrowed()<<"|"<<
    transaction->transaction.getDueDate()<<"|"<<
    transaction->transaction.getMemberID()<<"|"<<
    transaction->member->getMemberName()<<"|"<<
    transaction->member->getMemberSurname()<<"|"<<
    transaction->transaction.getBookID()<<"|"<<
    transaction->book->getAuthorsName()<<"|"<<
    transaction->book->getAuthorsSurname()<<"|"<<
    transaction->book->getTitle()<<"|"<<endl;
}

bool TransactionsCoordinator::showTransactionsByMember(int memberId)
{
    TransactionNode* currentTransactionNode = firstOfTransactions;
    system("cls"); bool found = false;
    cout<<"-----WYPOZYCZENIA-----\n\n";
    if (currentTransactionNode == NULL){
        cout<<"Baza danych jest pusta. Dodaj wypozyczenia."<<"\n";
        cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
        getch();
        return false;
    }
    while(currentTransactionNode != NULL){
        if (currentTransactionNode->transaction.getMemberID() == memberId){
            showSingleTransaction(currentTransactionNode);
            found = true;
        }
        currentTransactionNode = currentTransactionNode->next;
    }

    delete currentTransactionNode;
    currentTransactionNode = NULL;
    return found;
}

void TransactionsCoordinator::showTransactions()
{
    TransactionNode* currentTransactionNode = firstOfTransactions;
    system("cls");
    cout<<"-----WYPOZYCZENIA-----\n\n";
    if (currentTransactionNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj wypozyczenia."<<"\n";
    else
    {
        while(currentTransactionNode != NULL){
            showSingleTransaction(currentTransactionNode);
            currentTransactionNode = currentTransactionNode->next;
        }
    }
    delete currentTransactionNode;
    currentTransactionNode = NULL;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}

void TransactionsCoordinator::showOverdue()
{
    TransactionNode* currentTransactionNode = firstOfTransactions;
    system("cls");
    cout<<"-----WYPOZYCZENIA PRZETERMINOWANE-----\n\n";
    if (currentTransactionNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj wypozyczenia."<<"\n";
    else
    {
        while(currentTransactionNode != NULL){
           if(DataManipulation::getCurrentDate() > currentTransactionNode->transaction.getDueDate())
           {
                showSingleTransaction(currentTransactionNode);
                cout<<"Wygenerowano ponaglenie do przeterminowanego wypozyczenia"<<endl;
                fstream expired;
                string filename;
                filename = currentTransactionNode->member->getMemberName()+currentTransactionNode->member->getMemberSurname()+".txt";
                expired.open(filename, ios::app);
                if(expired.good()==true)
                {
                    expired<<"Szanowny/na "<<currentTransactionNode->member->getMemberName()<<" "<<currentTransactionNode->member->getMemberSurname()<<" z dniem "<<currentTransactionNode->transaction.getDueDate()<<" minal czas zwrotu ksiazki: "<<currentTransactionNode->book->getTitle()<<" autorstwa "<<currentTransactionNode->book->getAuthorsName()<<" "<<currentTransactionNode->book->getAuthorsSurname()<<". Prosimy o zwrot ksiazki do biblioteki w ciagu tygodnia od otrzymania ponaglenia. W przypadku braku zwrotu nalozona zostanie kara w wysokosci wartosci wypozyczonej ksiazki.\n"<<endl;
                    expired.close();
                }
                else
                {
                    cout<<"Nie udalo sie otworzyc pliku i zapisac do niego danych.";
                }
           }
            currentTransactionNode = currentTransactionNode->next;
        }
    }
    delete currentTransactionNode;
    currentTransactionNode = NULL;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}
