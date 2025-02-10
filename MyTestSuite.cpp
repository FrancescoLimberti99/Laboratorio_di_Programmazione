#include "MyTestSuite.h"

void MyTestSuite::setUp() {
    transaction = new Transaction(12345, 300.0, true, "spesa");
    sender = new BankAccount("Arthur Morgan","IT60X0542811101000000123456", 1000.0);
    receiver = new BankAccount("John Marston","IT60X0542811101000000654321", 500.0);
}

void MyTestSuite::tearDown() {
    delete transaction;
    delete sender;
    delete receiver;
}

void MyTestSuite::testTransactionConstructor() {
    TS_ASSERT_EQUALS(transaction->getId(), 12345);
    TS_ASSERT_DELTA(transaction->getAmount(), 300.0, 0.01);
    TS_ASSERT_EQUALS(transaction->getType(), true);
    TS_ASSERT_EQUALS(transaction->getMotivation(), "spesa");
}


void MyTestSuite::testTransactionTimestamp() {
    std::string initialTimestamp = transaction->getTimestamp();
    transaction->setTimestamp("01-01-2024 12:00:00");
    TS_ASSERT_EQUALS(transaction->getTimestamp(), "01-01-2024 12:00:00");

    // Test eccezioni: formato non valido
    try {
        transaction->setTimestamp("ciccio");
        TS_FAIL("Expected std::invalid_argument was not thrown");
    } catch (const std::invalid_argument& e) {
        TS_ASSERT_EQUALS(std::string(e.what()), "Formato del timestamp non valido");
    } catch (...) {
        TS_FAIL("Unexpected exception type thrown for invalid format");
    }

    // Test eccezioni: valori non validi
    try {
        transaction->setTimestamp("32-13-2024 12:00:00");
        TS_FAIL("Expected std::invalid_argument was not thrown");
    } catch (const std::invalid_argument& e) {
        TS_ASSERT_EQUALS(std::string(e.what()), "Valori del timestamp non validi");
    } catch (...) {
        TS_FAIL("Unexpected exception type thrown for invalid values");
    }
}

void MyTestSuite::testTransactionTransactionToString() {

    std::string expected = "Transaction:\n"
                           "- ID: 12345\n"
                           "- Amount: 300.0\n"
                           "- Type: Incoming\n"
                           "- Timestamp: " + transaction->getTimestamp() + "\n"
                           "- Motivation: spesa";

    TS_ASSERT_EQUALS(transaction->transactionToString(), expected);
}

void MyTestSuite::testTransactionWriteToFile() {
    transaction->writeToFile("test_transaction_write.txt");
}

void MyTestSuite::testTransactionModifyTransaction() {
    transaction->modifyTransaction(250.0, "12-12-2020 15:30:00", "rimborso");
    TS_ASSERT_DELTA(transaction->getAmount(), 250.0, 0.01);
    TS_ASSERT_EQUALS(transaction->getTimestamp(), "12-12-2020 15:30:00");
    TS_ASSERT_EQUALS(transaction->getMotivation(), "rimborso");
}

void MyTestSuite::testBankAccountConstructor() {
    TS_ASSERT_EQUALS(sender->getIban(), "IT60X0542811101000000123456");
    TS_ASSERT_DELTA(sender->getBalance(), 1000.0, 0.01);
    TS_ASSERT_EQUALS(sender->getSizeOfTransactions(), 0);
}


void MyTestSuite::testBankAccountAddTransaction() {
    sender->addTransaction(*transaction);
    TS_ASSERT_DELTA(sender->getBalance(), 1300.0, 0.01);
    TS_ASSERT_EQUALS(sender->getSizeOfTransactions(), 1);
}

void MyTestSuite::testBankAccountSendMoney() {
    sender->sendMoney(200.0, *receiver, "prova");
    TS_ASSERT_DELTA(sender->getBalance(), 800.0, 0.01);
    TS_ASSERT_DELTA(receiver->getBalance(), 700.0, 0.01);
    TS_ASSERT_EQUALS(sender->getSizeOfTransactions(), 1);
    TS_ASSERT_EQUALS(receiver->getSizeOfTransactions(), 1);

    // Test eccezioni: negative amount
    try {
        sender->sendMoney(-50.0, *receiver, "errore");
        TS_FAIL("Expected std::invalid_argument was not thrown");
    } catch (const std::invalid_argument& e) {
        TS_ASSERT_EQUALS(std::string(e.what()), "L'importo deve essere positivo.");
    } catch (...) {
        TS_FAIL("Unexpected exception type thrown for negative amount");
    }

    // Test eccezioni: amount > balance
    try {
        sender->sendMoney(1000.0, *receiver, "errore");
        TS_FAIL("Expected std::runtime_error was not thrown");
    } catch (const std::runtime_error& e) {
        TS_ASSERT_EQUALS(std::string(e.what()), "Saldo insufficiente per inviare il denaro.");
    } catch (...) {
        TS_FAIL("Unexpected exception type thrown for amount exceeding balance");
    }

}

void MyTestSuite::testBankAccountBankAccountToString() {

    std::string expected = "Bank Account:\n"
                           "-- General Info:\n"
                           "IBAN: IT60X0542811101000000123456\n"
                           "Balance: 1300.0\n"
                           "-- Transactions:\n"
                           "Transaction:\n"
                           "- ID: 12345\n"
                           "- Amount: 300.0\n"
                           "- Type: Incoming\n"
                           "- Timestamp: " + sender->getTransaction(1).getTimestamp() + "\n"
                           "- Motivation: spesa";

    TS_ASSERT_EQUALS(sender->bankAccountToString(), expected);
}

void MyTestSuite::testBankAccountWriteToFile() {
    sender->writeToFile("test_bankaccount_write.txt");
}

void MyTestSuite::testBankAccountWriteTransactionToFile() {
    sender->writeTransactionToFile(1,"test_bankaccount_write.txt");
}


void MyTestSuite::testBankAccountReadTransactionsFromFile() {
    sender->readTransactionsFromFile("test_bankaccount_read.txt");
    TS_ASSERT(sender->getSizeOfTransactions() > 0); // Supponendo che il file contenga transazioni.
}

void MyTestSuite::testBankAccountGetSizeOfTransaction() {
    TS_ASSERT_EQUALS(receiver->getSizeOfTransactions(), receiver->getTransactions().size());
}

void MyTestSuite::testBankAccountSearchTransactionByType() {
    sender->searchTransactionByType(true,"test_bankaccount_write.txt");
}

void MyTestSuite::testBankAccountSearchTransactionByTimestamp() {
    sender->searchTransactionByTimestamp("01-02-2018 12:30:00","test_bankaccount_write.txt");
}

void MyTestSuite::runAllTests() {

    setUp();

    //Transaction tests
    testTransactionConstructor();
    testTransactionTimestamp();
    testTransactionTransactionToString();
    testTransactionWriteToFile();
    testTransactionModifyTransaction();

    //BankAccount tests
    testBankAccountConstructor();
    testBankAccountAddTransaction();
    testBankAccountBankAccountToString();
    testBankAccountSendMoney();
    testBankAccountWriteToFile();
    testBankAccountWriteTransactionToFile();
    testBankAccountReadTransactionsFromFile();
    testBankAccountGetSizeOfTransaction();
    testBankAccountSearchTransactionByType();
    testBankAccountSearchTransactionByTimestamp();

    tearDown();

}










