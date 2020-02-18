//
//  BSTree.cpp
//  Program 5
//
//  Created by Gurjepaul Brar on 11/30/19.
//  Copyright © 2019 Gurjepaul Brar. All rights reserved.
//

#include <stdio.h>
#include "BSTree.h"

BSTree::BSTree()
{
    root = NULL;
}

BSTree::~BSTree()
{
    this->Empty();
}

bool BSTree::Insert(Account *inserting)
{
    // Make inserting the root if the Tree is empty
    if (root == NULL)
    {
        root = new Node;
        root->pAcct = inserting;
        return true;
    }
    // Call the recursive insert method that will put it in the appropriate position 
    else
    {
        Node *current = root;
        return RecInsert(current, inserting);
    }
}

bool BSTree::Retrieve(const int &accountID, Account *&retreiving) const
{
    Node *currentNode = root;
    bool finishedSearching = false;

    // While loop that searches the BSTree
    while (!finishedSearching)
    {
        // If the current Node is the Account we are looking for
        if (currentNode != NULL && accountID == (currentNode->pAcct)->getAccountID())
        {
            // Once we find our target, we set make the pointer reference equal to it
            retreiving = currentNode->pAcct;
            return true;
        }
        // Searches the right Node of the current Node if the account ID passed in is greater
        else if (currentNode != NULL && accountID > (currentNode->pAcct)->getAccountID())
        {
            currentNode = currentNode->right;
        }
        // Searches the left Node of the current Node if the account ID passed in is less
        else if (currentNode != NULL && accountID < (currentNode->pAcct)->getAccountID())
        {
            currentNode = currentNode->left;
        }
        // If we reach here, then the Account isn't found so we break the loop
        else
        {
            finishedSearching = true;
        }
    }
    
    return false; // Account is not located in the BSTree
}

void BSTree::Display() const
{
    // Tree is empty if the root is null
    if (root == NULL)
    {
        cerr << "ERROR: No accounts currently in the system" << endl;
    }
    // Calls a recursive method that prints each Node in the Tree
    else
    {
        RecPrint(root);
    }
}

void BSTree::Empty()
{
    delete root;
    root = NULL;
}

bool BSTree::isEmpty() const
{
    if (root == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BSTree::RecInsert(Node* currentNode, Account* inserting)
{
    // If the inserting account ID is greater than that of the current Node
    if (inserting->getAccountID() > (currentNode->pAcct)->getAccountID())
    {
        // If we reach the end of a branch where we can add the account
        if (currentNode->right == NULL)
        {
            Node *insertAcct = new Node();
            insertAcct->pAcct = inserting;
            currentNode->right = insertAcct;
            return true;
        }
        // Recursive call until we reach the end of a branch
        else
        {
            return RecInsert(currentNode->right, inserting);
        }

    }
    // If the inserting account ID is lesser than that of the current Node
    else if(inserting->getAccountID() < (currentNode->pAcct)->getAccountID()  )
    {
        // If we reach the end of a branch where we can add the account
        if (currentNode->left == NULL)
        {
            Node *insertAcct = new Node();
            insertAcct->pAcct = inserting;
            currentNode->left = insertAcct;
            return true;
        }
        // Recursive call until we reach the end of a branch
        else
        {
            return RecInsert(currentNode->left, inserting);
        }

    }
    // Failure to add inserting to the Tree
    else
    {
        return false;
    }
}


void BSTree::RecPrint(Node* currentNode) const
{
    // If the current Node has Nodes for both both branches
    if (currentNode->left != NULL && currentNode->right != NULL)
    {
        RecPrint(currentNode->right);
        cout << *(currentNode->pAcct) << endl;
        RecPrint(currentNode->left);
    }
    // If the current Node only has a Node for the left branch
    else if (currentNode->left != NULL)
    {
        cout << *(currentNode->pAcct) << endl;
        RecPrint(currentNode->left);
    }
    // If the current Node only has a Node for the right branch
    else if (currentNode->right != NULL)
    {
        cout << *(currentNode->pAcct) << endl;
        RecPrint(currentNode->right);
    }
    // If the root is the only Node in the tree
    else
    {
        cout << *(currentNode->pAcct) << endl;
    }

}
