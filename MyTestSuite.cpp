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

void MyTestSuite::testBankAccountSendMoney() { //TODO ASSERT/throw for exceptions
    sender->sendMoney(200.0, *receiver, "prova");
    TS_ASSERT_DELTA(sender->getBalance(), 800.0, 0.01);
    TS_ASSERT_DELTA(receiver->getBalance(), 700.0, 0.01);
    TS_ASSERT_EQUALS(sender->getSizeOfTransactions(), 1);
    TS_ASSERT_EQUALS(receiver->getSizeOfTransactions(), 1);
}


void MyTestSuite::testBankAccountWriteToFile() {
    sender->writeToFile("test_bankaccount_write.txt");
}


void MyTestSuite::testBankAccountReadTransactionsFromFile() {
    sender->readTransactionsFromFile("test_bankaccount_read.txt");
    TS_ASSERT(sender->getSizeOfTransactions() > 0); // Supponendo che il file contenga transazioni.
}

void MyTestSuite::testBankAccountGetSizeOfTransaction() {
    TS_ASSERT_EQUALS(receiver->getSizeOfTransactions(), receiver->getTransactions().size());
}

void MyTestSuite::runAllTests() {
    setUp();

    //Transaction tests
    testTransactionConstructor();
    testTransactionTimestamp();
    testTransactionWriteToFile();
    testTransactionModifyTransaction();

    //BankAccount tests
    testBankAccountConstructor();
    testBankAccountAddTransaction();
    testBankAccountSendMoney();
    testBankAccountWriteToFile();
    testBankAccountReadTransactionsFromFile();
    testBankAccountGetSizeOfTransaction();

    tearDown();

}






