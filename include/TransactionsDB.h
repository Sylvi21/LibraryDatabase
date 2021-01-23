#ifndef TRANSACTIONSDB_H
#define TRANSACTIONSDB_H
#include "TransactionsStruct.h"
#include "DataManipulation.h"
#include <iostream>
#include <fstream>


using namespace std;

class TransactionsDB
{
    private:
    string transactionsFileName = "Transactions.txt";
    int lastTransactionID;
    TransactionNode* firstOfTransactions;
    TransactionNode* lastOfTransactions;
    public:
        TransactionsDB();
        virtual ~TransactionsDB();
        TransactionNode* getFront();
        TransactionNode* getBack();
        TransactionNode* loadTransactionsFromFile();
        TransactionNode* findSpot(TransactionNode* transactions, Transaction transaction);
        int getLastTransactionID();
        int setLastTransactionID(string dataLine);
        string getFilename();
        bool addTransactionToDB(Transaction transaction);
        Transaction getSingleTransactionFromFile(string dataLine, int lastTransactionID);
        void editTransactionInDB(Transaction transactionsFileName);
        void removeTransactionFromDB(int ID);

};

#endif // TRANSACTIONSDB_H
