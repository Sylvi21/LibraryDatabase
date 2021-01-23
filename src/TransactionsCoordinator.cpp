#include "TransactionsCoordinator.h"

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
        while(tempMember != NULL && tempMember->member.getID() != ID)
            tempMember = tempMember->next;
        currentNode->member = &(tempMember->member);
        //get Book
        ID = currentNode->transaction.getBookID();
        BookNode *tempBook = frontBookNode;
        while(tempBook != NULL && tempBook->book.getID() != ID)
            tempBook = tempBook->next;
        currentNode->book = &(tempBook->book);
        //next transaction

        if(counter == 1)
            firstOfTransactions = currentNode;
        currentNode=currentNode->next;
    }
}

TransactionNode* TransactionsCoordinator::getTransactionById(int id){
    TransactionNode* currentNode = firstOfTransactions;
    while(currentNode != NULL && currentNode->transaction.getID() == id)
        currentNode=currentNode->next;
    return currentNode;
}

string TransactionsCoordinator::getCurrentDate(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%m/%d/%Y ", timeinfo);
    string str(buffer);
    return str;
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

    string date = "";

    TransactionNode* transactionNode = new TransactionNode();
    transactionNode->member = member;
    transactionNode->book = book;
    transactionNode->transaction.setID(transactionsDB->getLastTransactionID()+1);
    transactionNode->transaction.setBookID(book->getID());
    transactionNode->transaction.setMemberID(member->getID());
    date = getCurrentDate();
    transactionNode->transaction.setDateBorrowed(date);
 //   transactionNode->dueDate(date + 3 mce trzeba zrobiæ)

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
/*
void TransactionsCoordinator::registerReturn(int id)
{
    int removedId;
    TransactionNode *transactionNode = getTransactionById(id);
    if(transactionNode == NULL){
        cout << "Nie udalo sie odnalezc wypozyczenia o ID "<<id<<"! \n";
    }
    if(transactionsDB->removeTransactionFromDB(transactionNode->transaction.getID())){
        transactionNode->book->setStatus("dostepna");
        removedId = removeTransaction(transactionNode);
        if(removedId != 0){
            cout << "Zarejestrowano zwrot.\n";
        } else {
            cout << "Wystapil blad w programie. Nie udalo sie zarejestrowac zwrotu.\n";
        }
    } else {
        cout << "Wystapil blad z dostepem do bazy danych. Nie udalo sie zarejestrowac zwrotu.\n";
    }
    cout << "Kliknij dowolny klawisz, aby powrocic" << "\n";
    getch();
}
*/
void TransactionsCoordinator::removeTransaction(TransactionNode* node){
    TransactionNode *tmp = NULL;
    if(firstOfTransactions == NULL)
        return;
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
    return;
}

void TransactionsCoordinator::showSingleTransaction(TransactionNode* transaction)
{
    cout<<transaction->transaction.getID()<<" "<<
    transaction->member->getMemberName()<<" "<<
    transaction->member->getMemberSurname()<<" "<<
    transaction->book->getAuthorsName()<<" "<<
    transaction->book->getAuthorsSurname()<<" "<<
    transaction->book->getTitle()<<endl;
}

void TransactionsCoordinator::showTransactionsByMember(int memberId){
    TransactionNode* currentTransactionNode = firstOfTransactions;
    system("cls");
    cout<<"-----WYPOZYCZENIA-----\n\n";
    if (currentTransactionNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj wypozyczenia."<<"\n";
    else
    {
        while(currentTransactionNode != NULL && currentTransactionNode->member->getID() == memberId){
            showSingleTransaction(currentTransactionNode);
            currentTransactionNode = currentTransactionNode->next;
        }
    }
    delete currentTransactionNode;
    currentTransactionNode = NULL;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
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

}
