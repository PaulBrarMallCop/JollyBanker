//
//  Transaction.cpp
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#include <stdio.h>
#include "Transaction.h"

Transaction::Transaction(){}

Transaction::Transaction(char transactionType, string lastName, string firstName, int accountID)
{
    this->transactionType = transactionType;
    this->lastName = lastName;
    this->firstName = firstName;
    this->accountID = accountID;
}

Transaction::Transaction(char transactionType, int accountID, int accountType, int amount, string error)
{
    this->transactionType = transactionType;
    this->accountID = accountID;
    this->accountType = accountType;
    this->amount = amount;
    this->error = error;
}

Transaction::Transaction(char transactionType, int accountID, int accountType, int amount, int receivingID, int receivingType, string error)
{
    this->transactionType = transactionType;
    this->accountID = accountID;
    this->accountType = accountType;
    this->amount = amount;
    this->receivingID = receivingID;
    this->receivingType = receivingType;
    this->error = error;
}

Transaction::Transaction(char transactionType, int accountID, int accountType)
{
    this->transactionType = transactionType;
    this->accountID = accountID;
    this->accountType = accountType;
}

Transaction::Transaction(char transactionType, int accountID)
{
    this->transactionType = transactionType;
    this->accountID = accountID;
    this->accountType = -1;
}

Transaction::~Transaction(){}

char Transaction::getTransactionType() const
{
    return transactionType;
}

string Transaction::getFirstName() const
{
    return firstName;
}

string Transaction::getLastName() const
{
    return lastName;
}

string Transaction::getError() const
{
    return error;
}

int Transaction::getAccountID() const
{
    return accountID;
}

int Transaction::getAccountType() const
{
    return accountType;
}

int Transaction::getReceivingID() const
{
    return receivingID;
}

int Transaction::getReceivingType() const
{
    return receivingType;
}

int Transaction::getAmount() const
{
    return amount;
}

void Transaction::setTransactionType(char transactionType)
{
    this->transactionType = transactionType;
}

void Transaction::setFirstName(string firstName)
{
    this->firstName = firstName;
}

void Transaction::setLastName(string lastName)
{
    this->lastName = lastName;
}

void Transaction::setError(string error)
{
    this->error = error;
}

void Transaction::setAccountID(int accountID)
{
    this->accountID = accountID;
}

void Transaction::setAccountType(int accountType)
{
    this->accountType = accountType;
}

void Transaction::setReceivingID(int receivingID)
{
    this->receivingID = receivingID;
}

void Transaction::setReceivingType(int receivingType)
{
    this->receivingType = receivingType;
}

void Transaction::setAmount(int amount)
{
    this->amount = amount;
}

ostream& operator<<(ostream &os, const Transaction &other)
{
    if (other.getTransactionType() == 'O')
    {
        os << other.getTransactionType() << " " << other.getFirstName() << " " << other.getLastName() << " " << other.getAccountID();
    }
    else if (other.getTransactionType() == 'D' || other.getTransactionType() == 'W')
    {
        os << other.getTransactionType() << " " << other.getAccountID() << other.getAccountType() << " " << other.getAmount() << " " << other.getError();
    }
    else if (other.getTransactionType() == 'T')
    {
        os << other.getTransactionType() << " " << other.getAccountID() << other.getAccountType() << " " << other.getAmount() << " " << other.getReceivingID() << other.getReceivingType() << " " << other.getError();
    }
    else if (other.getTransactionType() == 'H')
    {
        os << other.getTransactionType() << " " << other.getAccountID() << other.getAccountType();
    }
    
    return os;
}
