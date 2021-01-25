#include "TransactionsCoordinator.h"
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
        cout<<"Member ID = "<<ID<<endl;
        MemberNode *tempMember = frontMemberNode;
        while(tempMember != NULL || tempMember->member.getID()!= ID){
            cout<<"counter: "<<counter<<endl;
            cout<<"tempMember.member = "<<tempMember->member.getID()<<endl;
            if(tempMember->member.getID()== ID)
                break;
            tempMember = tempMember->next;

   /*     if(tempMember->next != NULL)
            cout<<"tempMember.next = "<<tempMember->next->member.getID()<<endl;
        if(tempMember->prev != NULL)
            cout<<"tempMember.prev = "<<tempMember->prev->member.getID()<<endl;*/
        }
        currentNode->member = &(tempMember->member);
        cout<<"currentNode->member = "<<currentNode->member->getMemberSurname()<<endl;
        //get Book
        ID = currentNode->transaction.getBookID();
        cout<<"Book ID = "<<ID<<endl;
        BookNode *tempBook = frontBookNode;
        while(tempBook != NULL || tempBook->book.getID() != ID){
            cout<<"counter: "<<counter<<endl;
            cout<<"tempBook.book = "<<tempBook->book.getID()<<endl;
            if(tempBook->book.getID() == ID)
                break;
            tempBook = tempBook->next;
   /*     if(tempBook->next != NULL)
            cout<<"tempBook.next = "<<tempBook->next->book.getID()<<endl;
        if(tempBook->prev != NULL)
            cout<<"tempBook.prev = "<<tempBook->prev->book.getID()<<endl;*/
        }
        currentNode->book = &(tempBook->book);
        //next transaction

 /*       if(counter == 1)
            firstOfTransactions = currentNode;*/
        counter ++;
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

Book* TransactionsCoordinator::registerReturn(int id)
{
    int removedId; Book* book = NULL;
    TransactionNode *transactionNode = getTransactionById(id);
    if(transactionNode == NULL){
        cout << "Nie udalo sie odnalezc wypozyczenia o ID "<<id<<"! \n";
    }
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
    transaction->transaction.getMemberID()<<"|"<<
    transaction->member->getMemberName()<<"|"<<
    transaction->member->getMemberSurname()<<"|"<<
    transaction->transaction.getBookID()<<"|"<<
    transaction->book->getAuthorsName()<<"|"<<
    transaction->book->getAuthorsSurname()<<"|"<<
    transaction->book->getTitle()<<"|"<<endl;
}

bool TransactionsCoordinator::showTransactionsByMember(int memberId){
    TransactionNode* currentTransactionNode = firstOfTransactions;
    system("cls"); bool found = false;
    cout<<"-----WYPOZYCZENIA-----\n\n";
    if (currentTransactionNode == NULL)
        cout<<"Baza danych jest pusta. Dodaj wypozyczenia."<<"\n";
        cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
        getch();
        return false;

    while(currentTransactionNode != NULL){
        if (currentTransactionNode->member->getID() == memberId){
            showSingleTransaction(currentTransactionNode);
        }
        currentTransactionNode = currentTransactionNode->next;
    }

    delete currentTransactionNode;
    currentTransactionNode = NULL;
    cout<<"\nKliknij dowolny klawisz, aby powrocic"<<"\n";
    getch();
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

}
