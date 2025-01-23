#include "Transaction.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

Transaction::Transaction(int id, double amount, bool type, const string& motivation) : id(id), amount(amount), type(type), motivation(motivation) {

    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive.");
    }

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

string Transaction::getMotivation() const {
    return motivation;
}

string Transaction::getTimestamp() const {
    return timestamp;
}

void Transaction::setAmount(double amount) {
    Transaction::amount = amount;
}

void Transaction::setMotivation(const string &motivation) {
    Transaction::motivation = motivation;
}

void Transaction::setTimestamp(const string& timestamp) {

    // Controllo validità del nuovo timestamp
    int day, month, year, hour, minute, second;
    char delim1, delim2, space, colon1, colon2;

    std::istringstream ss(timestamp);
    ss >> day >> delim1 >> month >> delim2 >> year >> space >> hour >> colon1 >> minute >> colon2 >> second;

    if (ss.fail() || delim1 != '-' || delim2 != '-' || space != ' ' || colon1 != ':' || colon2 != ':') {
        throw std::invalid_argument("Formato del timestamp non valido");
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        throw std::invalid_argument("Valori del timestamp non validi");
    }

    // setter
    Transaction::timestamp = timestamp;
}

void Transaction::writeToFile(const string& filename) const {
    ofstream file(filename, ios::app); // classe ofstream per scrivere su file, ios::app significa che è in modalità append (aggiunge in coda)
    if (file.is_open()) {
        file << "Transaction:" << "\n";
        file << "- ID: " << id << "\n";
        file << "- Amount: " << amount << "\n";
        file << "- Type: " << (type ? "Incoming" : "Outcoming") << "\n";
        file << "- Timestamp: " << timestamp << "\n";
        file << "- Motivation: " << motivation << "\n";
        file << "----------------------" << "\n";
        file.close();
    } else {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
    }
}

void Transaction::modifyTransaction(double amount, const string &timestamp, const string &motivation) {
    setAmount(amount);
    setTimestamp(timestamp);
    setMotivation(motivation);
}

Transaction::~Transaction() {}







