//
//  Fund.h
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#ifndef Fund_h
#define Fund_h

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"
using namespace std;

class Fund
{
public:
    // Constructors and Destructor
    Fund();
    Fund(string accountTitle);
    ~Fund();
    
    // Getters and Setters
    int getBalance() const;
    string getAccountTitle() const;
    void setBalance(int amount);
    void setAccountTitle(string accountTitle);
    bool isEmpty() const;
    
    // Class functions
    bool AddAmount(int amount);
    bool SubtractAmount(int amount);
    void AddFundHistory(Transaction transaction);
    void PrintFundHistory() const;
    
private:
    int balance;
    string accountTitle;
    vector<Transaction> fundHistory;
};
#endif /* Fund_h */
