//
//  Bank.h
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#ifndef Bank_h
#define Bank_h

#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "BSTree.h"
#include "Transaction.h"
using namespace std;

class Bank
{
public:
    // Constructor and Destructor
    Bank();
    ~Bank();
    
    void Display() const;
private:
    queue<Transaction> transactions;
    BSTree accounts;
    
    // Class functions
    void ReadTransactions();
    void ProcessTransactions();
};
#endif /* Bank_h */
