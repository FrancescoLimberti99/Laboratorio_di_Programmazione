//
// Created by Home PC on 03/12/2024.
//

#include "BankAccount.h"
#include <fstream>
#include <iostream>

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

void BankAccount::writeToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << "IBAN: " << iban << "\n";
        file << "Balance: " << balance << "\n";
        file << "----------------------" << "\n";

        for (const auto& transaction : transactions) {
            file << "Transaction ID: " << transaction.getId() << "\n";
            file << "Amount: " << transaction.getAmount() << "\n";
            file << "Type: " << (transaction.getType() ? "Entrata" : "Uscita") << "\n";
            file << "----------------------" << "\n";
        }

        file << "----------------------" << "\n";
        file.close();
    } else {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
    }
}

void BankAccount::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);

    if (transaction.getType()) {
        balance += transaction.getAmount();
    } else {
        balance -= transaction.getAmount();
    }
}

