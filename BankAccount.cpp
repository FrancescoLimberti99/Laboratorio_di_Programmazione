#include "BankAccount.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>

bool isEarlier(const string& timestamp1, const string& timestamp2) {    // utilizzata in searchTransactionsByTimestamp()

    int day1, month1, year1, hour1, minute1, second1;
    int day2, month2, year2, hour2, minute2, second2;
    char delim1, delim2, space1, colon1, colon2;
    char delim3, delim4, space2, colon3, colon4;

    std::istringstream ss1(timestamp1);
    ss1 >> day1 >> delim1 >> month1 >> delim2 >> year1 >> space1 >> hour1 >> colon1 >> minute1 >> colon2 >> second1;
    std::istringstream ss2(timestamp2);
    ss2 >> day2 >> delim3 >> month2 >> delim4 >> year2 >> space2 >> hour2 >> colon3 >> minute2 >> colon4 >> second2;

    if (year1 != year2)
        return year1 < year2;
    if (month1 != month2)
        return month1 < month2;
    if (day1 != day2)
        return day1 < day2;
    if (hour1 != hour2)
        return hour1 < hour2;
    if (minute1 != minute2)
        return minute1 < minute2;
    return second1 < second2;
}

using namespace std;

BankAccount::BankAccount(const string& name, const string& iban, double balance)
        : name(name), iban(iban), balance(balance) {}

string BankAccount::getIban() const {
    return iban;
}

double BankAccount::getBalance() const {
    return balance;
}

vector<Transaction> BankAccount::getTransactions() const {
    return transactions;
}

Transaction BankAccount::getTransaction(int a) {
    if (getSizeOfTransactions() < a) {
        throw invalid_argument("Non ci sono abbastanza elementi per fornire l'elemento richiesto");
    }
    return transactions[a-1];
}

string BankAccount::bankAccountToString() const {
    std::ostringstream oss;
    oss << "Bank Account:\n"
        << "-- General Info:" << "\n"
        << "IBAN: " << iban << "\n"
        << "Balance: " << balance << "\n"
        << "-- Transactions:" << "\n";

        for (const auto& transaction : transactions) {
            oss << transaction.transactionToString() << "\n";
        }
    return oss.str();
}

void BankAccount::writeToFile(const string& filename) const {
    ofstream file(filename, ios::app); // classe ofstream per scrivere su file, ios::app significa che è in modalità append (aggiunge)
    if (file.is_open()) {
        file << bankAccountToString() << "\n----------------------\n";
        file << "----------------------" << "\n";
        file << "----------------------" << "\n";
        file.close();

    } else {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
    }
}

void BankAccount::writeTransactionToFile(int a, const string& filename) {
    if (getSizeOfTransactions() < a) {
        throw invalid_argument("Non ci sono abbastanza elementi per fornire l'elemento richiesto");
    }
    transactions[a-1].writeToFile(filename);
}

void BankAccount::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);

    if (transaction.getType()) {
        balance += transaction.getAmount();
    } else {
        balance -= transaction.getAmount();
    }
}

void BankAccount::sendMoney(double amount, BankAccount& receiver, const string& motivation) {
    if (amount <= 0) {
        throw invalid_argument("L'importo deve essere positivo.");
    }
    if (balance < amount) {
        throw runtime_error("Saldo insufficiente per inviare il denaro.");
    }


    int transactionId = rand() % 90000 + 10000;

    Transaction senderTransaction(transactionId, amount, false, motivation); // false = uscita
    Transaction receiverTransaction(transactionId, amount, true, motivation); // true = entrata

    addTransaction(senderTransaction);
    receiver.addTransaction(receiverTransaction);
}

void BankAccount::readTransactionsFromFile(const string& filename) {
    ifstream file(filename); // ifstream classe per aprire il file per la sola lettura
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file " << filename << endl;
        return;
    }

    string line;
    int transactionId;
    double amount;
    bool type;
    string timestamp;
    string motivation;

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
            getline(ss >> std::ws, timestamp); // estrae timestamp della transaction
            // std::cout << timestamp << std::endl;

            getline(file, line); // riga successiva
            ss.clear();
            ss.str(line);
            ss >> temp >> temp;
            getline(ss, motivation); // estrae motivation della transaction

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
                Transaction newTransaction(transactionId, amount, type, motivation);
                newTransaction.setTimestamp(timestamp);
                addTransaction(newTransaction);
            }
        }
    }

    file.close();
}

int BankAccount::getSizeOfTransactions() {
    return transactions.size();
}

void BankAccount::searchTransactionByType(bool type, const string& filename) {
    for (const auto& transaction : transactions) {
        if (transaction.getType() == type) {
            transaction.writeToFile(filename);
        }
    }
}

void BankAccount::searchTransactionByTimestamp(const string &timestamp, const string& filename) {

    // Controllo validità del timestamp
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

    string a;
    
    for (const auto& transaction : transactions) {
        a = transaction.getTimestamp();

        if (isEarlier(a, timestamp)) {    // la funzione isEarlier() è stata definita in alto
            transaction.writeToFile(filename);
        }

    }
}






