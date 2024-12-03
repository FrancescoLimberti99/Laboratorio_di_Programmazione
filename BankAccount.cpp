//
// Created by Home PC on 03/12/2024.
//

#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount(const string& iban, double balance)
        : iban(iban), balance(balance) {}

string BankAccount::getIban() const {
    return iban;
}

double BankAccount::getBalance() const {
    return balance;
}

vector<Transaction> BankAccount::getTransactions() const {
    return transactions;
}