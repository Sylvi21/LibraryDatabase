#include "TransactionsDB.h"

TransactionsDB::TransactionsDB()
{
    this->firstOfTransactions = NULL;
    this->lastOfTransactions = NULL;
    this->lastTransactionID = 0;
}

TransactionsDB::~TransactionsDB()
{
    //dtor
}

TransactionNode* TransactionsDB::getFront()
{
    return firstOfTransactions;
}

TransactionNode* TransactionsDB::getBack()
{
    return lastOfTransactions;
}

void TransactionsDB::loadTransactionsFromFile()
{
    string dataLine="", lastTransactionDataLine="";
    TransactionNode* pom = NULL;
    TransactionNode* temp = new TransactionNode();
    temp = NULL;
    Transaction singleTransaction;
    fstream transactionsFile;
    transactionsFile.open("Transactions.txt", ios::in);

    if (transactionsFile.good() == true)
    {
        while (getline(transactionsFile, dataLine))
        {
            singleTransaction = getSingleTransactionFromFile(dataLine);
            TransactionNode* newTransactionNode = new TransactionNode();
            newTransactionNode->transaction = singleTransaction;

            if (firstOfTransactions == NULL) {
                firstOfTransactions = newTransactionNode;
                lastOfTransactions = newTransactionNode;
                newTransactionNode->prev = NULL;
                newTransactionNode->next = NULL;
            } else {
                temp = findSpot(singleTransaction);
                if(firstOfTransactions == temp){
                    newTransactionNode->next = firstOfTransactions;
                    firstOfTransactions->prev = newTransactionNode;
                    newTransactionNode->prev = NULL;
                    firstOfTransactions = newTransactionNode;
                } else if (temp == NULL){
                    lastOfTransactions->next = newTransactionNode;
                    newTransactionNode->prev = lastOfTransactions;
                    newTransactionNode->next = temp;
                    lastOfTransactions = newTransactionNode;
                } else {
                    pom=temp->prev;
                    pom->next=newTransactionNode;
                    newTransactionNode->prev=temp->prev;
                    temp->prev=newTransactionNode;
                    newTransactionNode->next=temp;
                }
            }
            lastTransactionDataLine = dataLine;
        }
        transactionsFile.close();
    }
    if (lastTransactionDataLine != "")
    {
        this->lastTransactionID = setLastTransactionID(lastTransactionDataLine);
    }
    delete temp;
    temp = NULL;
    delete pom;
    pom = NULL;
}

int TransactionsDB::getLastTransactionID(){
    return lastTransactionID;
}

int TransactionsDB::setLastTransactionID(string dataLine)
{
    int newID = DataManipulation::extractNumber(dataLine, 1);
    lastTransactionID = newID;

    return lastTransactionID;
}

TransactionNode* TransactionsDB::findSpot(Transaction transaction)
{
    TransactionNode* transactions = firstOfTransactions;
    while(transactions != NULL && transactions->transaction.getID() < transaction.getID())
        transactions=transactions->next;

    return transactions;
}

Transaction TransactionsDB::getSingleTransactionFromFile(string dataLine)
{
    Transaction singleTransaction;
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
            case 1:
                singleTransaction.setID(stoi(subLine.c_str()));
                break;
            case 2:
                singleTransaction.setMemberID(stoi(subLine.c_str()));
                break;
            case 3:
                singleTransaction.setBookID(stoi(subLine.c_str()));
                break;
            case 4:
                singleTransaction.setDateBorrowed(subLine);
                break;
            case 5:
                singleTransaction.setDueDate(subLine);
                break;
            }
            subLine="";
            subLineNumber++;
        }
    }
    return singleTransaction;
}

bool TransactionsDB::addTransactionToDB(Transaction transaction)
{

    fstream transactionsDB;
    transactionsDB.open(getFilename(), ios::app);
    if(transactionsDB.good()==true)
    {
        transactionsDB<<transaction.getID()<<"|";
        transactionsDB<<transaction.getMemberID()<<"|";
        transactionsDB<<transaction.getBookID()<<"|";
        transactionsDB<<transaction.getDateBorrowed()<<"|";
        transactionsDB<<transaction.getDueDate()<<"|"<<endl;

        transactionsDB.close();
        lastTransactionID++;
        return true;
    }
    else
    {
        cout<<"Nie udalo sie otworzyc pliku i zapisac do niego danych.";
        return false;
    }
}

string TransactionsDB::getFilename(){
    return transactionsFileName;
}


bool TransactionsDB::removeTransactionFromDB(int ID){
    ifstream inFile("Transactions.txt");
    ofstream outFile;
    outFile.open("temp.txt", ios::out | ios::app);

    string line="";
    string subLine;
    if(inFile.good())
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
            if(atoi(subLine.c_str()) == ID)
                continue;
            else
            {
                outFile<<line<<endl;
                lastTransactionID = atoi(subLine.c_str());
            }
        }
        outFile.close();
        inFile.close();
        remove("Transactions.txt");
        rename("temp.txt", "Transactions.txt");
        return true;
    }
    else
    {
        outFile.close();
        remove("temp.txt");
        return false;
    }
}
