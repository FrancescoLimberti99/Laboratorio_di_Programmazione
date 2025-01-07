#ifndef ELABORATO_BANKACCOUNT_H
#define ELABORATO_BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class BankAccount {
public:
    BankAccount(const string& iban, double balance); // costruttore

    string getIban() const; // getter per l'attributo iban

    double getBalance() const; // getter per l'attributo balance

    vector<Transaction> getTransactions() const; // getter per l'attributo transactions //TODO get the single transaction

    void writeToFile(const string& filename) const; // scrive su file

    //TODO write the single transaction

    void addTransaction(const Transaction& transaction); // aggiunge una transaction all'attributo transactions

    void sendMoney(double amount, BankAccount& receiver); // invia denaro ad un altro BankAccount (istanzia due transazioni con lo stesso id)

    void readTransactionsFromFile(const string& filename); // legge da file una transaction, la costruisce e la inserisce nell'attributo transactions

    //TODO search transaction (data/tipo)

    //TODO getsize(transactions)

private:
    string iban;
    double balance;
    vector<Transaction> transactions;
    //TODO add name

};

#endif //ELABORATO_BANKACCOUNT_H
