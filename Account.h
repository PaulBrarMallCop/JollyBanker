//
//  Account.h
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#ifndef Account_h
#define Account_h

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"
#include "Fund.h"
using namespace std;

class Account
{
public:
    // Constructor
    Account();
    Account(string firstName, string lastName, int accountID);
    ~Account();
    
    // Getters and Setters
    string getFirstName() const;
    string getLastName() const;
    int getAccountID() const;
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setAccountID(int accountID);
    
    // Class functions
    bool Deposit(Transaction &processing);
    bool Withdraw(Transaction &processing);
    bool Transfer(Transaction &processing, Account *&receiving);
    void PrintFundHistory(const Transaction &processing) const;
    void PrintHistory() const;
    
    // Overloading
    friend ostream& operator<<(ostream &os, const Account &other);
    
private:
    string firstName;
    string lastName;
    int accountID;
    vector<Fund> funds;
};
#endif /* Account_h */
