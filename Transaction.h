//
//  Transaction.h
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#ifndef Transaction_h
#define Transaction_h

#include <string>
#include <iostream>
using namespace std;

class Transaction
{
public:
    // Constructors and destructor
    Transaction();
    Transaction(char transactionType, string lastName, string firstName, int accountID);
    Transaction(char transactionType, int accountID, int accountType, int amount, string error);
    Transaction(char transactionType, int accountID, int accountType, int amount, int receivingID, int receivingType, string error);
    Transaction(char transactionType, int accountID, int accountType);
    Transaction(char transactionType, int accountID);
    ~Transaction();
    
    // Getters
    char getTransactionType() const;
    string getFirstName() const;
    string getLastName() const;
    string getError() const;
    int getAccountID() const;
    int getAccountType() const;
    int getReceivingID() const;
    int getReceivingType() const;
    int getAmount() const;
    // Setters
    void setTransactionType(char transactionType);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setError(string error);
    void setAccountID(int accountID);
    void setAccountType(int accountType);
    void setReceivingID(int receivingID);
    void setReceivingType(int receivingType);
    void setAmount(int amount);
    
    // Overloading
    friend ostream& operator<<(ostream &os, const Transaction &other);
    
private:
    char transactionType;
    string firstName, lastName, error;
    int accountID, accountType, amount, receivingID, receivingType;
};
#endif /* Transaction_h */
