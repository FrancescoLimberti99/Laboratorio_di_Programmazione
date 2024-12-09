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

    clearFile("test_transaction_write.txt");

    clearFile("test_bankaccount_write.txt");

    MyTestSuite suite;

    suite.runAllTests();

    return 0;
}