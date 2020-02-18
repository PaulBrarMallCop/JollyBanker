//
//  Account.cpp
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#include <stdio.h>
#include "Account.h"

Account::Account(){}

Account::Account(string firstName, string lastName, int accountID)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->accountID = accountID;
    
    string accountTitles[] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};
    
    // Initializing all the Fund objects in the funds vector with the appropriate account titles
    for (int i = 0; i < 10; i++)
    {
        funds.push_back(Fund(accountTitles[i]));
    }
}

Account::~Account(){
}

string Account::getFirstName() const
{
    return firstName;
}

string Account::getLastName() const
{
    return lastName;
}

int Account::getAccountID() const
{
    return accountID;
}

void Account::setFirstName(string firstName)
{
    this->firstName = firstName;
}

void Account::setLastName(string lastName)
{
    this->lastName = lastName;
}

void Account::setAccountID(int accountID)
{
    this->accountID = accountID;
}

bool Account::Deposit(Transaction &processing)
{
    bool pass = (funds[processing.getAccountType()]).AddAmount(processing.getAmount());
    
    if (!pass) // If the transaction failed
    {
        processing.setError("(Failed)");
        cerr << "ERROR: Cannot deposit a negative amount into " << firstName << " " << lastName << " " << (funds[processing.getAccountType()]).getAccountTitle() << endl;
    }
    
    (funds[processing.getAccountType()]).AddFundHistory(processing); // Adds to fund history
    return pass;
}

bool Account::Withdraw(Transaction &processing)
{
    bool pass = (funds[processing.getAccountType()]).SubtractAmount(processing.getAmount());
    
    // If the transaction failed but the account type is fund[0],[1],[2],[3]
    if (!pass && (processing.getAmount() > 0) && (processing.getAccountType() == 0 || processing.getAccountType() == 1 || processing.getAccountType() == 2 || processing.getAccountType() == 3))
    {
        // Following check if their is enough money for the combined accounts to complete the transaction
        bool moneyMarketsHaveEnough = (funds[0].getBalance() + funds[1].getBalance()) >= processing.getAmount();
        bool bondsHaveEnough = (funds[2].getBalance() + funds[3].getBalance()) >= processing.getAmount();
           
        if (moneyMarketsHaveEnough || bondsHaveEnough) // If the accounts can be combined
        {
            pass = true; // Set to true since the transaction is valid in this situation
            int desiredAmount, withdrawFund;
               
            if (processing.getAccountType() >= 0 || processing.getAccountType() <= 3)
            {
                // Sets up variables for a transaction from PMV to MM fund
                if (processing.getAccountType() == 0)
                {
                    desiredAmount = processing.getAmount() - funds[0].getBalance();
                    withdrawFund = 1;
                }
                // Sets up variables for a transaction from MM to PMV fund
                else if (processing.getAccountType() == 1)
                {
                    desiredAmount = processing.getAmount() - funds[1].getBalance();
                    withdrawFund = 0;
                }
                // Sets up variables for a transaction from STB to LTB fund
                else if (processing.getAccountType() == 2)
                {
                    desiredAmount = processing.getAmount() - funds[2].getBalance();
                    withdrawFund = 3;
                }
                // Sets up variables for a transaction from LTB to STB fund
                else
                {
                    desiredAmount = processing.getAmount() - funds[3].getBalance();
                    withdrawFund = 2;
                }
                   
                // Creates a new Transaction object for a transfer between the two mutual accounts
                Transaction withdrawDesired('W', accountID, withdrawFund, desiredAmount, "");
                
                processing.setAmount((funds[processing.getAccountType()]).getBalance());
                   
                // Subtracting and adding funds to/from the appropriate amounts
                funds[withdrawFund].SubtractAmount(desiredAmount);
                   
                // Adding to the transaction history of each fund
                funds[withdrawFund].AddFundHistory(withdrawDesired);
                
                // Subtracting the full balance from the initial account
                funds[processing.getAccountType()].SubtractAmount((funds[processing.getAccountType()]).getBalance()); 
            }
        }
    }
    
    if (!pass) // If the transaction failed
    {
        processing.setError("(Failed)");
        
        if (processing.getTransactionType() != 'T')
        {
            cerr << "ERROR: Not enough funds to withdraw " << processing.getAmount() << " from " << firstName << " " << lastName << " " << (funds[processing.getAccountType()]).getAccountTitle() << endl;
        }
    }
    
    (funds[processing.getAccountType()]).AddFundHistory(processing); // Adds to fund history does the WHOLE AMOUNT
    
    return pass;
}

bool Account::Transfer(Transaction &processing, Account *&receiving)
{
    bool pass = this->Withdraw(processing);
    
    // If the transaction failed but the account type is fund[0],[1],[2],[3]
    if (pass)
    {
        receiving->funds[processing.getReceivingType()].AddAmount(processing.getAmount());
    }
    else // Transaction cannot be completed
    {
        processing.setError("(Failed)");
        cerr << "ERROR: Not enough funds to withdraw " << processing.getAmount() << " from " << firstName << " " << lastName << " " << (funds[processing.getAccountType()]).getAccountTitle() << ". Transferal refused." << endl;
    }
    
    // Adding to the history of each fund
    (receiving->funds[processing.getReceivingType()]).AddFundHistory(processing);
        
    return pass;
}

void Account::PrintFundHistory(const Transaction &processing) const
{
    cout << "Transaction History for " << firstName << " " << lastName << " " << funds[processing.getAccountType()].getAccountTitle() << ": $" << funds[processing.getAccountType()].getBalance() << endl;
    funds[processing.getAccountType()].PrintFundHistory();
}

void Account::PrintHistory() const
{
    cout << "Transaction History for " << firstName << " " << lastName << " by fund." << endl;
    
    for (int i = 0; i < 10; i++)
    {
        if (!funds[i].isEmpty())
        {
            cout << funds[i].getAccountTitle() << ": $" << funds[i].getBalance() << endl;
            funds[i].PrintFundHistory();
        }
    }
}

ostream& operator<<(ostream &os, const Account &other)
{
    os << other.firstName << " " << other.lastName << " Account ID: " << other.accountID << endl;
    
    for (int i = 0; i < (other.funds).size(); i++)
    {
        os << "    " << (other.funds[i]).getAccountTitle() << ": $" << (other.funds[i]).getBalance() << endl;
    }
    
    return os;
}
