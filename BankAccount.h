//
// Created by Home PC on 03/12/2024.
//

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

private:
    string iban;
    double balance;
    vector<Transaction> transactions;

};

#endif //ELABORATO_BANKACCOUNT_H
