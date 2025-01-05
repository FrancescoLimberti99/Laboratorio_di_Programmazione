#ifndef ELABORATO_TRANSACTION_H
#define ELABORATO_TRANSACTION_H

#include <string>

using namespace std;

class Transaction {
public:

    Transaction(int id, double amount, bool type); // costruttore

    int getId() const; // getter per attributo id

    double getAmount() const; // getter per attributo amount

    bool getType() const; // getter per attributo type

    string getTimestamp() const; // getter per attributo timestamp

    void setTimestamp(const string& timestamp); // setter per attributo timestamp

    void writeToFile(const string& filename) const; // scrive la transazione sul file

private:
    int id;
    double amount;
    bool type; // 0 = uscita, 1 = entrata
    string timestamp;

};

#endif //ELABORATO_TRANSACTION_H
