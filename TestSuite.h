//
// Created by Home PC on 06/12/2024.
//

#ifndef ELABORATO_TESTSUITE_H
#define ELABORATO_TESTSUITE_H

#include <cxxtest/TestSuite.h>
#include <cxxtest/TestTracker.h>
#include "Transaction.h"
#include "BankAccount.h"

class TestSuite : public CxxTest::TestSuite {
public:

    void setUp();

    // tearDown() viene chiamato dopo ogni test
    void tearDown();

    // Tests per la classe Transaction
    void testTransactionConstructor();

    void testTransactionTimestamp();

    void testTransactionWriteToFile();

    void testTransaction();

    // Tests per la classe BankAccount
    void testBankAccountConstructor();

    void testBankAccountAddTransaction();

    void testBankAccountSendMoney();

    void testBankAccountWriteToFile();

    void testBankAccountReadTransactionsFromFile();

    void testBankAccount();

private:
    Transaction* t1;
    BankAccount* sender;
    BankAccount* receiver;
};

#endif //ELABORATO_TESTSUITE_H
