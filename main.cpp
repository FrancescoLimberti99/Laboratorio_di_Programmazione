#include <iostream>
#include <fstream>
#include "BankAccount.h"
#include "Transaction.h"

using namespace std;

void clearFile(const string& filename)  {
    ofstream file(filename, ios::trunc);

    if (!file) {
        cerr << "Errore nell'aprire il file: " << filename << endl;
    } else {
        cout << "Contenuto del file '" << filename << "' cancellato con successo." << endl;
    }
}

int main() {

    clearFile("Write.txt");

    BankAccount acc1("IT60X0542811101000000123456", 1000.0);

    acc1.writeToFile("Write.txt");

    Transaction t1(12345, 300.0, true);
    Transaction t2(56789, 100.0, false);

    t1.writeToFile("Write.txt");
    t2.writeToFile("Write.txt");

    acc1.addTransaction(t1);
    acc1.addTransaction(t2);

    acc1.writeToFile("Write.txt");

    BankAccount acc2("IT60X0542811101000000654321", 500.0);

    acc2.writeToFile("Write.txt");

    try {
        acc1.sendMoney(200.0, acc2);

        acc1.writeToFile("Write.txt");
        acc2.writeToFile("Write.txt");

        cout << "Trasferimento completato con successo!" << endl;
    } catch (const exception& e) {
        cerr << "Errore durante il trasferimento: " << e.what() << endl;
    }

    try {
        acc2.sendMoney(100.0, acc1);

        acc1.writeToFile("Write.txt");
        acc2.writeToFile("Write.txt");

        cout << "Trasferimento completato con successo!" << endl;
    } catch (const exception& e) {
        cerr << "Errore durante il trasferimento: " << e.what() << endl;
    }

    cout << "Operazioni completate con successo. Controlla il file Write.txt." << endl;

    BankAccount acc3("IT60X0542811101000000321654", 1200.0);

    acc3.readTransactionsFromFile("Read.txt");

    acc3.writeToFile("Write.txt");


    return 0;
}
