#ifndef ELABORATO_TRANSACTION_H
#define ELABORATO_TRANSACTION_H

#include <string>

using namespace std;

class Transaction {
public:

    Transaction(int id, double amount, bool type, const string& motivation); // costruttore

    int getId() const; // getter per attributo id

    double getAmount() const; // getter per attributo amount

    bool getType() const; // getter per attributo type

    string getTimestamp() const; // getter per attributo timestamp

    string getMotivation() const; // getter per attributo motivation

    void setAmount(double amount); // setter per attributo amount

    void setTimestamp(const string& timestamp); // setter per attributo timestamp

    void setMotivation(const string &motivation); // setter per attributo motivation

    string transactionToString() const; // trasforma le info di una transazione in una stringa

    void writeToFile(const string& filename) const; // scrive la transazione sul file

    void modifyTransaction(double amount, const string& timestamp, const string& motivation ); // modifica la transazione

    virtual ~Transaction();

private:
    int id;
    double amount;
    bool type; // 0 = uscita, 1 = entrata
    string timestamp;
    string motivation; // causale

};

#endif //ELABORATO_TRANSACTION_H
