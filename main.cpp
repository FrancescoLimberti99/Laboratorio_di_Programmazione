#include <iostream>
#include <fstream>
#include "BankAccount.h"
#include "Transaction.h"

using namespace std;

void clearFile(const string& filename)  {
    ofstream file(filename, ios::trunc); // classe ofstream per modificare il file, ios::trunc significa che elimina qualcosa

    if (!file) {
        cerr << "Errore nell'aprire il file: " << filename << endl;
    } else {
        cout << "Contenuto del file '" << filename << "' cancellato con successo." << endl;
    }
}

int main() {

    //TODO do a better main

    clearFile("Write.txt"); // pulisco il file dove scriverò

    BankAccount acc1("Arthur Morgan", "IT60X0542811101000000123456", 1000.0); // istanzio il  BankAccount acc1

    acc1.writeToFile("Write.txt"); // scrivo su file

    Transaction t1(12345, 300.0, true, "rimborso"); // istanzio due Transaction t1 e t2
    Transaction t2(56789, 100.0, false, "multa");

    t1.writeToFile("Write.txt"); // scrivo su file
    t2.writeToFile("Write.txt");

    acc1.addTransaction(t1); // aggiungo le Transaction t1 e t2 al BankAccount acc1
    acc1.addTransaction(t2);

    acc1.writeToFile("Write.txt"); // scrivo su file

    BankAccount acc2("John Marston","IT60X0542811101000000654321", 500.0); // istanzio il BankAccount acc2

    acc2.writeToFile("Write.txt"); // scrivo su file

    try {
        acc1.sendMoney(200.0, acc2, "acquisto"); // acc1 invia denaro a acc2

        acc1.writeToFile("Write.txt"); // scrivo su file
        acc2.writeToFile("Write.txt");

        cout << "Trasferimento completato con successo!" << endl;
    } catch (const exception& e) {
        cerr << "Errore durante il trasferimento: " << e.what() << endl;
    }

    try {
        acc2.sendMoney(100.0, acc1, "resto"); // ac2 invia denaro a acc2

        acc1.writeToFile("Write.txt"); // scrivo su file
        acc2.writeToFile("Write.txt");

        cout << "Trasferimento completato con successo!" << endl;
    } catch (const exception& e) {
        cerr << "Errore durante il trasferimento: " << e.what() << endl;
    }

    cout << "Operazioni completate con successo. Controlla il file Write.txt." << endl;

    BankAccount acc3("Dutch Van der Linde", "IT60X0542811101000000321654", 1200.0); // istanzio il BankAccount acc3

    acc3.readTransactionsFromFile("Read.txt"); // leggo da file e inserisco nelle Transaction del BankAccount

    acc3.writeToFile("Write.txt"); // scrivo su file


    return 0;
}
