#include <iostream>
#include "BankAccount.h"
#include "Transaction.h"

using namespace std;

int main() {

    BankAccount account("IT60X0542811101000000123456", 1000.0);

    account.writeToFile("Prova.txt");

    Transaction t1(12345, 300.0, true);
    Transaction t2(56789, 100.0, false);

    t1.writeToFile("Prova.txt");
    t2.writeToFile("Prova.txt");

    account.addTransaction(t1);
    account.addTransaction(t2);

    account.writeToFile("Prova.txt");

    cout << "Operazioni completate con successo. Controlla il file Prova.txt." << endl;

    return 0;
}
