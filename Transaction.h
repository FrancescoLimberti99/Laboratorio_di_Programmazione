//
// Created by Home PC on 03/12/2024.
//

#ifndef ELABORATO_TRANSACTION_H
#define ELABORATO_TRANSACTION_H

#include <string>

using namespace std;

class Transaction {
public:

    Transaction(int id, double amount, bool type);

    int getId() const;

    double getAmount() const;

    bool getType() const;

    void writeToFile(const string& filename) const;

private:
    int id;
    double amount;
    bool type; // 0 = uscita, 1 = entrata

};

#endif //ELABORATO_TRANSACTION_H
