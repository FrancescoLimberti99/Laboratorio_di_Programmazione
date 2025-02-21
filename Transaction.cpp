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

    // Controllo validità del nuovo timestamp ** RICHIESTA DURANTE REVISIONE
    std::tm tm = {};
    std::istringstream ss(timestamp);

    ss >> std::get_time(&tm, "%d-%m-%Y %H:%M:%S");

    if (ss.fail()) {
        throw std::invalid_argument("Formato del timestamp non valido");
    }

    tm.tm_isdst = -1;  // Lascia che il sistema decida se è ora legale
    if (mktime(&tm) == -1) {
        throw std::invalid_argument("Valori del timestamp non validi");
    }

    // setter
    Transaction::timestamp = timestamp;
}

string Transaction::transactionToString() const {
    std::ostringstream oss;
    oss << "Transaction:\n"
        << "- ID: " << id << "\n"
        << "- Amount: " << amount << "\n"
        << "- Type: " << (type ? "Incoming" : "Outgoing") << "\n"
        << "- Timestamp: " << timestamp << "\n"
        << "- Motivation: " << motivation;
    return oss.str();
}

void Transaction::writeToFile(const string& filename) const {
    ofstream file(filename, ios::app); // classe ofstream per scrivere su file, ios::app significa che è in modalità append (aggiunge in coda)
    if (file.is_open()) {
        file << transactionToString() << "\n----------------------\n";
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








