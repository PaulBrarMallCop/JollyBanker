//
//  Bank.cpp
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#include <stdio.h>
#include "Bank.h"

Bank::Bank()
{
    ReadTransactions();
    ProcessTransactions();
}

Bank::~Bank(){}

void Bank::ReadTransactions()
{
    ifstream input("BankTransIn.txt");
    
    if (!input)
    {
        cerr << "ERROR: Invalid input file" << endl;
        return;
    }
    
    // Variables that will be used as arguments to create transactions
    string readLine, firstName, lastName;
    char transactionType;
    int accountID, accountType, amount, receivingID, receivingType;
    
    while (!input.eof())
    {
        getline(input, readLine); // Reads the line and stores it in a string variable
        istringstream parseLine(readLine); // Parses the string and splits it up after spaces
        parseLine >> transactionType; // Stores the transaction type
        
        // If the transaction wants to open and account
        if (toupper(transactionType) == 'O')
        {
            parseLine >> lastName >> firstName >> accountID;
    
            transactions.push(Transaction(transactionType, lastName, firstName, accountID));
        }
        // If the transaction wants to make a deposit or a withdrawal
        else if (toupper(transactionType) == 'D' || transactionType == 'W')
        {
            parseLine >> accountID >> amount;
            
            accountType = accountID % 10; // Computes the account type by leaving the number at the end
            accountID = accountID / 10; // Computes the account ID by removing the number at the end
                
            transactions.push(Transaction(transactionType, accountID, accountType, amount, ""));
        }
        // If the transaction wants to make a transfer
        else if (toupper(transactionType) == 'T')
        {
            parseLine >> accountID >> amount >> receivingID;
            
            accountType = accountID % 10;
            accountID = accountID / 10;
                
            receivingType = receivingID % 10;
            receivingID = receivingID / 10;
                
            transactions.push(Transaction(transactionType, accountID, accountType, amount, receivingID, receivingType, ""));
        }
        // If the transaction wants to display account history
        else if (toupper(transactionType) == 'H')
        {
            parseLine >> accountID;
            
            if (accountID >= 10000 && accountID <= 99999)
            {
                accountType = accountID % 10;
                accountID = accountID / 10;
                                
                transactions.push(Transaction(transactionType, accountID, accountType));

            }
            else
            {
                transactions.push(Transaction(transactionType, accountID));
            }
        }
        // If the transaction type is invalid
        else
        {
            cerr << "ERROR: Transaction type: '" << transactionType << "' is invalid" << endl;
        }
    }
    input.close();
}

void Bank::ProcessTransactions()
{
    while (!transactions.empty())
    {
        bool isOpen; // Will hold a boolean value depending on whether an account is already open or not
        Account *currentAccount;
        
        Transaction processing = transactions.front(); // Gets the next Transaction in the queue
        
        // Opening an account
        if (processing.getTransactionType() == 'O')
        {
            // Checks to see if the account ID is a valid value
            if (processing.getAccountID() >= 1000 && processing.getAccountID() <= 9999)
            {
                isOpen = accounts.Retrieve(processing.getAccountID(), currentAccount);
                
                // If the account is not already open create a new Account object and add it to the BSTree
                if (!isOpen)
                {
                    Account *creating = new Account(processing.getFirstName(), processing.getLastName(), processing.getAccountID());
                    accounts.Insert(creating);
                }
                // Else the account is already open
                else
                {
                    cerr << "ERROR: Account " << processing.getAccountID() << " is already open. Transaction refused." << endl;
                }
            }
            // Account ID is invalid
            else
            {
                cerr << "ERROR: Invalid account number. Must be between 1000-9999." << endl;
            }
        }
        // Making a deposit
        else if (processing.getTransactionType() == 'D')
        {
            // Checks to see if the account ID/account type is a valid value
            if (processing.getAccountID() >= 1000 && processing.getAccountID() <= 9999)
            {
                isOpen = accounts.Retrieve(processing.getAccountID(), currentAccount);

                // If the account is already open attempt to make the deposit
                if (isOpen)
                {
                    currentAccount->Deposit(processing);
                }
                // Else the account is not found
                else
                {
                    cerr << "ERROR: Account " << processing.getAccountID() << " not found. Deposit refused." << endl;
                }
            }
            // Account ID is invalid
            else
            {
                cerr << "ERROR: Invalid account number. Deposit refused." << endl;
            }
        }
        // Making a withdrawal
        else if (processing.getTransactionType() == 'W')
        {
            // Checks to see if the account ID is a valid value
            if (processing.getAccountID() >= 1000 && processing.getAccountID() <= 9999)
            {
                isOpen = accounts.Retrieve(processing.getAccountID(), currentAccount);
                
                // If the account is already open attempt to make the withdrawal
                if (isOpen)
                {
                    currentAccount->Withdraw(processing);
                }
                // Else the account is not found
                else
                {
                    cerr << "ERROR: Account " << processing.getAccountID() << " not found. Withdrawal refused." << endl;
                }
            }
            // Account ID is invalid
            else
            {
                cerr << "ERROR: Invalid account number. Withdrawal refused." << endl;
            }
        }
        // Making a transfer between accounts
        else if (processing.getTransactionType() == 'T')
        {
            // Checks to see if the account and receiving account information is valid
            if ((processing.getAccountID() >= 1000 && processing.getAccountID() <= 9999) && (processing.getReceivingID() >= 1000 && processing.getReceivingID() <= 9999))
            {
                Account *receiving;
                
                isOpen = accounts.Retrieve(processing.getAccountID(), currentAccount);
                bool retreivingIsOpen = accounts.Retrieve(processing.getReceivingID(), receiving);
                
                // If both accounts are open attempt to make the transfer
                if (isOpen && retreivingIsOpen)
                {
                    currentAccount->Transfer(processing, receiving);
                }
                // Else if the intitial account isn't found
                else if (!isOpen && !retreivingIsOpen)
                {
                    cerr << "ERROR: Invalid account number/s. Transferal refused" << endl;
                }
                // Else if the initial account isn't found
                else if (!isOpen)
                {
                    cerr << "ERROR: Account " << processing.getAccountID() << " not found. Transferal refused." << endl;
                }
                // Else if the receiving account isn't found
                else if (!retreivingIsOpen)
                {
                    cerr << "ERROR: Account " << processing.getReceivingID() << " not found. Transferal refused." << endl;
                }
            }
            // If the the sending/receiving account information is invalid
            else
            {
                cerr << "ERROR: Invalid account number/s. Transferal refused" << endl;
            }
        }
        // Displaying account information
        else
        {
            isOpen = accounts.Retrieve(processing.getAccountID(), currentAccount);
            
            // If the account is already open attempt to make the withdrawal
            if (isOpen)
            {
                // If the transaction wants the history of a specific fund
                if (processing.getAccountType() >= 0 && processing.getAccountType() <= 9)
                {
                    currentAccount->PrintFundHistory(processing);
                }
                // If the transaction wants the history of every fund in the account
                else
                {
                    currentAccount->PrintHistory();
                }
            }
            // Else if the account number is invalid
            else if (processing.getAccountID() < 1000 || processing.getAccountID() > 9999)
            {
                cerr << "ERROR: Invalid account number. Must be between 1000-9999." << endl;
            }
            // Else the account information is invalid
            else
            {
                cerr << "ERROR: Account " << processing.getAccountID() << " not found. Cannot display history." << endl;
            }
        }
        transactions.pop(); // Taking the completed Transaction out of the queue
    }
}

void Bank::Display() const
{
    cout << endl;
    cout << "Processing Done. Final Balances." << endl;
    accounts.Display();
}
