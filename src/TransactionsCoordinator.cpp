#include "TransactionsCoordinator.h"

TransactionsCoordinator::TransactionsCoordinator(TransactionNode* firstOfTransactions, TransactionNode* lastOfTransactions, TransactionsDB *transactionsDB)
{
    this->transactionsDB = transactionsDB;
    this->firstOfTransactions = firstOfTransactions;
    this->lastOfTransactions = lastOfTransactions;
}

TransactionsCoordinator::~TransactionsCoordinator()
{

}

string getCurrentDate(){
    time_t now = time(0);
    struct tm  tstruct;
    char buffer[80];
    tstruct = *localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &tstruct);

    return buffer;
}

TransactionNode* TransactionsCoordinator::findSpot(TransactionNode transaction)
{
    TransactionNode* currentNode = firstOfTransactions;
    while(currentNode != NULL && currentNode->ID < transaction.ID)
        currentNode=currentNode->next;
    return currentNode;
}

void TransactionsCoordinator::lendBook(MemberNode *memberNode, BookNode *bookNode)
{
    string date = "";
    TransactionNode* pom = NULL;
    TransactionNode* temp = NULL;

    TransactionNode* transaction = new TransactionNode();
//    transaction->ID = transactionsDB->getLastTransactionID()+1;
//    date = getCurrentDate();
 //   transaction->dateBorrowed = date;
   // transaction->dueDate(date + 3 mce trzeba zrobiæ)

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
    currentTransactionNode = NULL;
    delete currentTransactionNode;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
}
void TransactionsCoordinator::showOverdue()
{

}
