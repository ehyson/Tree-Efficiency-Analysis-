//
//  BST.h
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include "BSTNode.h"
#include <iostream>

using namespace std;


class BST
{
public:
    BST();
    ~BST();
    BSTNode *getRoot() {return root;}
    BSTNode *getMax( BSTNode *node );
    
    void insert( int data );
    void remove( int data );
    void search( int data );
    void clear( BSTNode *node );
    void printTree( BSTNode *node );
    
    int getCount() {return count;}
    int getCompare() {return compare;}
    
    bool isEmpty() {return root == NULL;}
    
    string type = "Binary Search";

private:
    int count;
    int compare;
    
    BSTNode *root;
    
};




/*****************************************************************************
 *                            constructors                                   *
 ****************************************************************************/
BST::BST()
{
    root = NULL;
    
    count = 0;
    compare = 0;
}





BST::~BST()
{
    this->clear(root);
    
    count = 0;
    compare = 0;
}





/*****************************************************************************
 *                            public methods                                 *
 ****************************************************************************/
void BST::insert( int data )
{
    BSTNode *iNode = new BSTNode();
    BSTNode *parent = NULL;
    
    iNode->data = data;
    iNode->left = NULL;
    iNode->right = NULL;
    
    
    if( isEmpty() )
    {
        compare++;
        root = iNode;
    }
    else
    {
        compare++;
        BSTNode *current = root;
        
        while( current != NULL )
        {
            
            parent = current;
            
            if( data > current->data )
            {
                compare++;
                current = current->right;
            }
            else
            {
                compare++;
                current = current->left;
            }
        }
        
        if( data > parent->data )
        {
            compare++;
            parent->right = iNode;
        }
        else
        {
            compare++;
            parent->left = iNode;
        }
    }
    count++;
}





void BST::remove( int data )
{
    BSTNode *current = root;
    BSTNode *parent = current;
    
    
    if( this->isEmpty() )
    {
        cout << "Binary Search Tree is Empty " << endl << endl;
        compare++;
        return;
    }
    
    //Remove Root
    if( current->data == data )
    {
        if( current->left == NULL )
            root = root->right;
        else
        {
            BSTNode *temp = getMax(current->left);
            int maxLeftSub = temp->data;
            remove( maxLeftSub );
            this->root->data = maxLeftSub;
        }
       
    }
    
    while( current != NULL )
    {
        
        if( current->data == data )
        {
            compare++;
            count--;
            break;
        }
        else
        {
            parent = current;
            if( current->data > data )
            {
                compare++;
                current = current->left;
            }
            else
            {
                compare++;
                current = current->right;
            }
        }
    }
    
    
    
    if( current == NULL )
    {
        compare++;
        cout << data << " was not found in Binary Search Tree!" << endl;
        return;
    }

    
    if( current->left == NULL && current->right == NULL )
    {
        compare+=2;
        if( parent->left == current )
        {
            compare++;
            parent->left = NULL;
        }
        else if( parent->right == current )
        {
            compare++;
            parent->right = NULL;
        }
        
        delete current;
        return;
    }
    
    
    if (current->left != NULL && current->right == NULL)
    {
        compare+=2;
        if (parent->left == current)
        {
            compare++;
            parent->left = current->left;
            delete current;
        }
        else
        {
            compare++;
            parent->right = current->left;
            delete current;
            
        }
        return;
    }
    
    
    if (current->left == NULL && current->right != NULL)
    {
        compare+=2;
        if (parent->left == current)
        {
            compare++;
            parent->left = current->right;
            delete current;
            
        }
        else
        {
            compare++;
            parent->right = current->right;
            delete current;
        }
        return;
    }
    
   
    if (current->left != NULL && current->right != NULL)
    {
        compare+=2;
        BSTNode* temp = current->right;
        
        if (temp->left == NULL && temp->right == NULL)
        {
            compare++;
            current->data = temp->data;
            current->right = NULL;
            delete temp;
            return;
        }
        else
        {
            compare++;

            if ( (current->right)->left != NULL )
            {
                BSTNode* temp2 = (current->right)->left;
                BSTNode* temp3 = current->right;
                
                while (temp2->left != NULL)
                {
                    compare++;
                    temp3 = temp2;
                    temp2 = temp2->left;
                }
                
                compare++;
                current->data = temp2->data;
                temp3->left = NULL;
                delete temp2;
                return;
                
            }
            else
            {
                compare++;
                BSTNode* temp = current->right;
                current->data = temp->data;
                current->right = temp->right;
                delete temp;
                return;
            }
        }
    }
}





void BST::search( int data )
{
    bool found = false;
    BSTNode *current = root;
    BSTNode *parent;
    
    while( current != NULL )
    {
        compare++;
        parent = current;
        
        if( data < current->data )
        {
            compare++;
            current = current->left;
        }
        else if( data > current->data )
        {
            compare++;
            current = current->right;
        }
        else if( data == current->data )
        {
            compare++;
            found = true;
            break;
        }
    }
    
    if( !found )
    {
        cout << data << " was not found in Binary Search Tree!" << endl;
    }
}





void BST::clear( BSTNode *node )
{
    if( node != NULL )
    {
        clear( node->left );
        clear( node->right );
        delete node;
    }
    
    count = 0;
}



BSTNode* BST::getMax( BSTNode *node )
{
    if( node == NULL )
    {
        compare++;
        return NULL;
    }
    else if( node->right == NULL )
    {
        compare++;
        return node;
    }
    else
    {
        compare++;
        return getMax( node->right );
    }
}



void BST::printTree( BSTNode *node )
{
    if( node == NULL )
    {
        return;
    }
    else
    {
        cout << "[" << node->data;
        printTree( node->left );
        
        if( (node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL) )
        {
            cout << "[]";
        }
        
        printTree( node->right );
        cout << "]";
    }
}


#endif /* BST_h */
