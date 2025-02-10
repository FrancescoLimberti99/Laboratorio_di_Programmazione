#include <fstream>
#include <iostream>
#include "MyTestSuite.h"

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

    clearFile("test_transaction_write.txt"); // pulisce il file

    clearFile("test_bankaccount_write.txt"); // pulisce il file

    MyTestSuite suite; // istanzia una suite per i test

    suite.runAllTests(); // esegue il metodo runAllTests() che svolge tutti i test

    return 0;
}