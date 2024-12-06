//
// Created by Home PC on 06/12/2024.
//

#include "TestSuite.h"

void TestSuite::setUp() {
    // Inizializza gli oggetti necessari per i test
    t1 = new Transaction(12345, 300.0, true);  // Un esempio di transazione
    sender = new BankAccount("IT60X0542811101000000123456", 1000.0);
    receiver = new BankAccount("IT60X0542811101000000654321", 500.0);
}

void TestSuite::tearDown() {
    // Pulisci le risorse se necessario
    delete t1;
    delete sender;
    delete receiver;
}

void TestSuite::testTransactionConstructor() {
    TS_ASSERT_EQUALS(t1->getId(), 12345);
    TS_ASSERT_DELTA(t1->getAmount(), 300.0, 0.01);
    TS_ASSERT_EQUALS(t1->getType(), true);
}


void TestSuite::testTransactionTimestamp() {
    std::string initialTimestamp = t1->getTimestamp();
    t1->setTimestamp("01-01-2024 12:00:00");
    TS_ASSERT_EQUALS(t1->getTimestamp(), "01-01-2024 12:00:00");
}


void TestSuite::testTransactionWriteToFile() {
    t1->writeToFile("test_transaction_write.txt");
}

void TestSuite::testTransaction() {
    testTransactionConstructor();
    testTransactionTimestamp();
    testTransactionWriteToFile();
}

void TestSuite::testBankAccountConstructor() {
    TS_ASSERT_EQUALS(sender->getIban(), "IT60X0542811101000000123456");
    TS_ASSERT_DELTA(sender->getBalance(), 1000.0, 0.01);
    TS_ASSERT_EQUALS(sender->getTransactions().size(), 0);
}


void TestSuite::testBankAccountAddTransaction() {
    sender->addTransaction(*t1);
    TS_ASSERT_DELTA(sender->getBalance(), 1300.0, 0.01);
    TS_ASSERT_EQUALS(sender->getTransactions().size(), 1);
}

void TestSuite::testBankAccountSendMoney() {
    sender->sendMoney(200.0, *receiver);
    TS_ASSERT_DELTA(sender->getBalance(), 800.0, 0.01);
    TS_ASSERT_DELTA(receiver->getBalance(), 700.0, 0.01);
    TS_ASSERT_EQUALS(sender->getTransactions().size(), 1);
    TS_ASSERT_EQUALS(receiver->getTransactions().size(), 1);
}


void TestSuite::testBankAccountWriteToFile() {
    sender->writeToFile("test_bankaccount_write.txt");
}


void TestSuite::testBankAccountReadTransactionsFromFile() {
    sender->readTransactionsFromFile("test_bankaccount_read.txt");
    TS_ASSERT(sender->getTransactions().size() > 0); // Supponendo che il file contenga transazioni.
}


void TestSuite::testBankAccount() {
    testBankAccountConstructor();
    testBankAccountAddTransaction();
    testBankAccountSendMoney();
    testBankAccountWriteToFile();
    testBankAccountReadTransactionsFromFile();
}
