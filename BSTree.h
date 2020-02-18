//
//  BSTree.h
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#ifndef BSTree_h
#define BSTree_h
#include "Account.h"
using namespace std;

class BSTree
{
public:
    BSTree();
    ~BSTree();
    
    bool Insert(Account *inserting);
    
    // retrieve object, first parameter is the ID of the account
    // second parameter holds the pointer to found object, NULL if not found
    bool Retrieve(const int &accountID, Account *&retreiving) const;
    
    // displays the contents of a tree to cout
    void Display() const;
    void Empty();
    bool isEmpty() const;
    
private:
    struct Node
    {
        Account *pAcct = NULL;
        Node *right = NULL;
        Node *left = NULL;
    };
    Node *root;
    
    // Recursive helpers
    bool RecInsert(Node* currentNode, Account* inserting);
    void RecPrint(Node* currentNode) const;
};
#endif /* BSTree_h */
