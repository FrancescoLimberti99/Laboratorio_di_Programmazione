//
// Created by Home PC on 03/12/2024.
//

#ifndef ELABORATO_TRANSACTION_H
#define ELABORATO_TRANSACTION_H

class Transaction {
public:

    Transaction(double id, int amount, bool type);

    double getId() const;

    int getAmount() const;

    bool getType() const;

private:
    double id;
    int amount;
    bool type; // 0 = uscita, 1 = entrata

};

#endif //ELABORATO_TRANSACTION_H
