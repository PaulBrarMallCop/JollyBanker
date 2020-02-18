//
//  Fund.cpp
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#include <stdio.h>
#include "Fund.h"

Fund::Fund()
{
    balance = 0;
}

Fund::Fund(string accountTitle)
{
    this->accountTitle = accountTitle;
    balance = 0;
}

Fund::~Fund(){}

int Fund::getBalance() const
{
    return balance;
}

string Fund::getAccountTitle() const
{
    return accountTitle;
}

void Fund::setBalance(int amount)
{
    balance = amount;
}

void Fund::setAccountTitle(string accountTitle)
{
    this->accountTitle = accountTitle;
}

bool Fund::isEmpty() const
{
    if (fundHistory.size() > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Fund::AddAmount(int amount)
{
    if (amount < 0)
    {
        return false;
    }
    
    balance += amount;
    return true;
}

bool Fund::SubtractAmount(int amount)
{
    if (amount < 0 || amount > balance)
    {
        return false;
    }
    
    balance -= amount;
    return true;
}

void Fund::AddFundHistory(Transaction transaction)
{
    fundHistory.push_back(transaction);
}

void Fund::PrintFundHistory() const
{
    for (int i = 0; i < fundHistory.size(); i++)
    {
        cout << "  " << fundHistory[i] << endl;
    }
}
