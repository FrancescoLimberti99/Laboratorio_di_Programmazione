//
// Created by Home PC on 03/12/2024.
//

#include "Transaction.h"

Transaction::Transaction(double id, int amount, bool type) : id(id), amount(amount), type(type) {}

double Transaction::getId() const {
    return id;
}

int Transaction::getAmount() const {
    return amount;
}

bool Transaction::getType() const {
    return type;
}