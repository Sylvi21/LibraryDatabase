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

void TransactionsCoordinator::lendBook(Member *member, Book *book)
{
    string date = "";
    TransactionNode* pom = NULL;
    TransactionNode* temp = NULL;

    book->setStatus("wypozyczona");
    TransactionNode* transaction = new TransactionNode();
    transaction->member = member;
    transaction->book = book;
    transaction->transaction.setID(transactionsDB->getLastTransactionID()+1);
    date = getCurrentDate();
    transaction->transaction.setDateBorrowed(date);
 //   transaction->dueDate(date + 3 mce trzeba zrobiæ)

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
void TransactionsCoordinator::registerReturn()
{

}

void TransactionsCoordinator::showSingleTransaction(Transaction transaction){
    cout<<transaction.getID()<<" "<<
    transaction.getBookID()<<" "<<
    transaction.getMemberID()<<endl;
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
            showSingleTransaction(currentTransactionNode->transaction);
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
