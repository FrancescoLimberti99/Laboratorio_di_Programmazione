#include "BankAccount.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

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
    ofstream file(filename, ios::app); // classe ofstream per scrivere su file, ios::app significa che è in modalità append (aggiunge)
    if (file.is_open()) {
        file << "Bank Account:" << "\n";
        file << "-- General Info:" << "\n";
        file << "IBAN: " << iban << "\n";
        file << "Balance: " << balance << "\n";
        file << "-- Transactions:" << "\n";

        for (const auto& transaction : transactions) {
            file << "Transaction:" << "\n";
            file << "- ID: " << transaction.getId() << "\n";
            file << "- Amount: " << transaction.getAmount() << "\n";
            file << "- Type: " << (transaction.getType() ? "Incoming" : "Outcoming") << "\n";
            file << "- Timestamp: " << transaction.getTimestamp() << "\n";
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

void BankAccount::sendMoney(double amount, BankAccount& receiver) {
    if (amount <= 0) {
        throw invalid_argument("L'importo deve essere positivo.");
    }
    if (balance < amount) {
        throw runtime_error("Saldo insufficiente per inviare il denaro.");
    }


    int transactionId = rand() % 90000 + 10000;

    Transaction senderTransaction(transactionId, amount, false); // false = uscita
    Transaction receiverTransaction(transactionId, amount, true); // true = entrata

    addTransaction(senderTransaction);
    receiver.addTransaction(receiverTransaction);
}

void BankAccount::readTransactionsFromFile(const string& filename) {
    ifstream file(filename); // ifstream classe per aprire il file in sola lettura
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
        return;
    }

    string line;
    int transactionId;
    double amount;
    bool type;
    string timestamp;

    while (getline(file, line)) {     // getline legge il file riga per riga
        if (line.find("Transaction:") != string::npos) {   // se trova Transaction: nella riga

            getline(file, line); // riga successiva
            stringstream ss(line);
            string temp;
            ss >> temp >> temp >> transactionId; // estrae id della transaction

            getline(file, line); // riga successiva
            ss.clear();
            ss.str(line);
            ss >> temp >> temp >> amount; // estrae amount della transaction

            getline(file, line); // riga successiva
            ss.clear();
            ss.str(line);
            string typeStr;
            ss >> temp >> temp >> typeStr; // estrae il il type della transaction
            type = (typeStr == "Incoming");

            getline(file, line); // riga successiva
            ss.clear();
            ss.str(line);
            ss >> temp >> temp;
            getline(ss, timestamp); // estrae timestamp della transaction

            // controlla duplicato
            bool isDuplicate = false;
            for (const auto& transaction : transactions) {
                if (transaction.getId() == transactionId) {
                    isDuplicate = true;
                    break;
                }
            }

            // se non è già presente istanzia una transazione con i dati estratti
            if (!isDuplicate) {
                Transaction newTransaction(transactionId, amount, type);
                newTransaction.setTimestamp(timestamp);
                addTransaction(newTransaction);
            }
        }
    }

    file.close();
}

