#ifndef ELABORATO_TESTSUITE_H
#define ELABORATO_TESTSUITE_H

#include <cxxtest/TestSuite.h>
#include <cxxtest/LinkedList.h>
#include "Transaction.h"
#include "BankAccount.h"

class MyTestSuite : public CxxTest::TestSuite {
public:

    void setUp();

    void tearDown();

    // Tests per la classe Transaction
    void testTransactionConstructor();

    void testTransactionTimestamp();

    void testTransactionWriteToFile();

    // Tests per la classe BankAccount
    void testBankAccountConstructor();

    void testBankAccountAddTransaction();

    void testBankAccountSendMoney();

    void testBankAccountWriteToFile();

    void testBankAccountReadTransactionsFromFile();

    void runAllTests();

private:
    Transaction* transaction;
    BankAccount* sender;
    BankAccount* receiver;
};

#endif //ELABORATO_TESTSUITE_H
