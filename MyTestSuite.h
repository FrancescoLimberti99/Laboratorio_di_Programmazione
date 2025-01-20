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

    // Tests per i metodi della classe Transaction
    void testTransactionConstructor();

    void testTransactionTimestamp();

    void testTransactionWriteToFile();

    void testTransactionModifyTransaction();

    // Tests per i metodi della classe BankAccount
    void testBankAccountConstructor();

    void testBankAccountAddTransaction();

    void testBankAccountSendMoney();

    void testBankAccountWriteToFile();

    void testBankAccountReadTransactionsFromFile();

    void testBankAccountGetSizeOfTransaction();

    //TODO add functions for new methods

    void runAllTests();

private:
    Transaction* transaction;
    BankAccount* sender;
    BankAccount* receiver;
};

#endif //ELABORATO_TESTSUITE_H
