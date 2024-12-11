#include "MyTestSuite.h"

void MyTestSuite::setUp() {
    transaction = new Transaction(12345, 300.0, true);
    sender = new BankAccount("IT60X0542811101000000123456", 1000.0);
    receiver = new BankAccount("IT60X0542811101000000654321", 500.0);
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
}


void MyTestSuite::testTransactionTimestamp() {
    std::string initialTimestamp = transaction->getTimestamp();
    transaction->setTimestamp("01-01-2024 12:00:00");
    TS_ASSERT_EQUALS(transaction->getTimestamp(), "01-01-2024 12:00:00");
}


void MyTestSuite::testTransactionWriteToFile() {
    transaction->writeToFile("test_transaction_write.txt");
}

void MyTestSuite::testBankAccountConstructor() {
    TS_ASSERT_EQUALS(sender->getIban(), "IT60X0542811101000000123456");
    TS_ASSERT_DELTA(sender->getBalance(), 1000.0, 0.01);
    TS_ASSERT_EQUALS(sender->getTransactions().size(), 0);
}


void MyTestSuite::testBankAccountAddTransaction() {
    sender->addTransaction(*transaction);
    TS_ASSERT_DELTA(sender->getBalance(), 1300.0, 0.01);
    TS_ASSERT_EQUALS(sender->getTransactions().size(), 1);
}

void MyTestSuite::testBankAccountSendMoney() {
    sender->sendMoney(200.0, *receiver);
    TS_ASSERT_DELTA(sender->getBalance(), 800.0, 0.01);
    TS_ASSERT_DELTA(receiver->getBalance(), 700.0, 0.01);
    TS_ASSERT_EQUALS(sender->getTransactions().size(), 1);
    TS_ASSERT_EQUALS(receiver->getTransactions().size(), 1);
}


void MyTestSuite::testBankAccountWriteToFile() {
    sender->writeToFile("test_bankaccount_write.txt");
}


void MyTestSuite::testBankAccountReadTransactionsFromFile() {
    sender->readTransactionsFromFile("test_bankaccount_read.txt");
    TS_ASSERT(sender->getTransactions().size() > 0); // Supponendo che il file contenga transazioni.
}

void MyTestSuite::runAllTests() {
    setUp();

    //Transaction methods tests
    testTransactionConstructor();
    testTransactionTimestamp();
    testTransactionWriteToFile();

    //BankAccount methods tests
    testBankAccountConstructor();
    testBankAccountAddTransaction();
    testBankAccountSendMoney();
    testBankAccountWriteToFile();
    testBankAccountReadTransactionsFromFile();

    tearDown();

}



