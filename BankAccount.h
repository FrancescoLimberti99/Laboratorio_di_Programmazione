#ifndef ELABORATO_BANKACCOUNT_H
#define ELABORATO_BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class BankAccount {
public:
    BankAccount(const string& name, const string& iban, double balance); // costruttore

    string getIban() const; // getter per l'attributo iban

    double getBalance() const; // getter per l'attributo balance

    vector<Transaction> getTransactions() const; // getter per l'attributo transactions

    Transaction getTransaction(int a); // getter per la singola transaction

    string bankAccountToString() const; // trasforma il bankaccount in una stringa

    void writeToFile(const string& filename) const; // scrive su file

    void writeTransactionToFile(int a, const string& filename); // scrive una transazione su file

    void addTransaction(const Transaction& transaction); // aggiunge una transaction all'attributo transactions

    void sendMoney(double amount, BankAccount& receiver, const string& motivation); // invia denaro ad un altro BankAccount (istanzia due transazioni con lo stesso id)

    void readTransactionsFromFile(const string& filename); // legge da file una transaction, la costruisce e la inserisce nell'attributo transactions

    int getSizeOfTransactions();

    void searchTransactionByType(bool type, const string& filename); // scrive su file tutte le transaction del tipo richiesto

    void searchTransactionByTimestamp(const string& timestamp, const string& filename); // scrive su file tutte le transaction antecedenti al timestamp passato come argomento

private:
    string name;
    string iban;
    double balance;
    vector<Transaction> transactions;

};

#endif //ELABORATO_BANKACCOUNT_H
