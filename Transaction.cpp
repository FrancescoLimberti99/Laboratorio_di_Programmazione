#include "Transaction.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

Transaction::Transaction(int id, double amount, bool type) : id(id), amount(amount), type(type) {

    //TODO check positive amount (throw exception)

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&now_time), "%d-%m-%Y %H:%M:%S"); // cattura l'istante di tempo
    timestamp = ss.str();
}

int Transaction::getId() const {
    return id;
}

double Transaction::getAmount() const {
    return amount;
}

bool Transaction::getType() const {
    return type;
}

string Transaction::getTimestamp() const {
    return timestamp;
}

void Transaction::setTimestamp(const string& timestamp) {
    //TODO check timestamp validity
    this->timestamp = timestamp;
}

void Transaction::writeToFile(const string& filename) const {
    ofstream file(filename, ios::app); // classe ofstream per scrivere su file, ios::app significa che è in modalità append (aggiunge in coda)
    if (file.is_open()) {
        file << "Transaction:" << "\n";
        file << "- ID: " << id << "\n";
        file << "- Amount: " << amount << "\n";
        file << "- Type: " << (type ? "Incoming" : "Outcoming") << "\n";
        file << "- Timestamp: " << timestamp << "\n";
        file << "----------------------" << "\n";
        file.close();
    } else {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
    }
}