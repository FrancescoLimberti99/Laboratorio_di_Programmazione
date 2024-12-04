//
// Created by Home PC on 03/12/2024.
//

#include "Transaction.h"
#include <fstream>
#include <iostream>

Transaction::Transaction(int id, double amount, bool type) : id(id), amount(amount), type(type) {}

int Transaction::getId() const {
    return id;
}

double Transaction::getAmount() const {
    return amount;
}

bool Transaction::getType() const {
    return type;
}

void Transaction::writeToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << "Transaction:" << "\n";
        file << "- ID: " << id << "\n";
        file << "- Amount: " << amount << "\n";
        file << "- Type: " << (type ? "Incoming" : "Outcoming") << "\n";
        file << "----------------------" << "\n";
        file.close();
    } else {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
    }
}