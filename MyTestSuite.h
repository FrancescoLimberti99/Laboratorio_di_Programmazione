#ifndef ELABORATO_TESTSUITE_H
#define ELABORATO_TESTSUITE_H

#include <cxxtest/TestSuite.h>
#include <cxxtest/LinkedList.h>
#include "Transaction.h"
#include "BankAccount.h"

class MyTestSuite : public CxxTest::TestSuite {
public:

    void setUp() override;

    void tearDown() override;

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

    void testBankAccountWriteTransactionToFile();

    void testBankAccountReadTransactionsFromFile();

    void testBankAccountGetSizeOfTransaction();

    void testBankAccountSearchTransactionByType();

    void testBankAccountSearchTransactionByTimestamp();

    void runAllTests();

private:
    Transaction* transaction;
    BankAccount* sender;
    BankAccount* receiver;
};

#endif //ELABORATO_TESTSUITE_H
