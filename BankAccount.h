#ifndef ELABORATO_BANKACCOUNT_H
#define ELABORATO_BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class BankAccount {
public:
    BankAccount(const string& iban, double balance);

    string getIban() const;

    double getBalance() const;

    vector<Transaction> getTransactions() const;

    void writeToFile(const string& filename) const;

    void addTransaction(const Transaction& transaction);

    void sendMoney(double amount, BankAccount& receiver);

    void readTransactionsFromFile(const string& filename);

private:
    string iban;
    double balance;
    vector<Transaction> transactions;

};

#endif //ELABORATO_BANKACCOUNT_H
