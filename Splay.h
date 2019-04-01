//
//  Splay.h
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#ifndef Splay_h
#define Splay_h

#include "SplayNode.h"
#include <iostream>

using namespace std;


class Splay
{
public:
    Splay();
    ~Splay();
    SplayNode* getRoot() {return root;}
    SplayNode* find( int data );
    
    void insert( int data );
    void remove( int data );
    void search( int data );
    void clear( SplayNode *node );
    void printTree( SplayNode *root );
    
    int getCount() {return count;}
    int getCompare() {return compare;}
    
    bool isEmpty() {return root == NULL;}
    
    string type = "Splay";
    
private:
    int count;
    int compare;
    
    SplayNode *root;
    
    void zig( SplayNode *node);
    void zigZig( SplayNode *node );
    void zigZag( SplayNode *node );
    SplayNode* splay( SplayNode *node );
    
    SplayNode *getMin( SplayNode *node );
    SplayNode *getMax( SplayNode *node );
    
};




/*****************************************************************************
 *                            constructors                                   *
 ****************************************************************************/
Splay::Splay()
{
    root = NULL;
    count = 0;
    compare = 0;
}





Splay::~Splay()
{
    clear( root );
    count = 0;
    compare = 0;
}



/*****************************************************************************
 *                            public methods                                 *
 ****************************************************************************/
void Splay::insert( int data )
{
    if( isEmpty() )
    {
        compare++;
        count++;
        SplayNode *newRoot = new SplayNode();
        newRoot->data = data;
        root = newRoot;
        return;
    }
    else
    {
        SplayNode *current = root;
        
        while( current != NULL )
        {
            compare++;
            if( data < current->data )
            {
                compare++;
                if( current->left == NULL )
                {
                    compare++;
                    SplayNode *iNode = new SplayNode();
                    iNode->data = data;
                    iNode->parent = current;
                    current->left = iNode;
                    count++;
                    splay( iNode );
                    return;
                }
                else
                {
                    compare++;
                    current = current->left;
                }
            }
            else if( data > current->data )
            {
                compare++;
                if( current->right == NULL )
                {
                    compare++;
                    SplayNode *iNode = new SplayNode;
                    iNode->data = data;
                    iNode->parent = current;
                    current->right = iNode;
                    count++;
                    splay( iNode );
                    return;
                }
                else
                {
                    compare++;
                    current = current->right;
                }
            }
            else
            {
                compare++;
                splay( current );
                return;
            }
        }
    }
}





void Splay::remove( int data )
{
  
    if( isEmpty() )
    {
        compare++;
        return;
    }
    else
    {
        
        SplayNode *temp;
        SplayNode *root = find( data );
        
        if( root->data != data )
        {
            return;
        }
         
        SplayNode *rightRoot = root->right;
        
        
        if( !root->left )
        {
            temp = root;
            root = root->right;
            root->parent = NULL;
        }
        else if( !root->right )
        {
            temp = root;
            root = root->left;
            root->parent = NULL;
        }
        else
        {
            temp = root;
            root->left->parent = NULL;
            root = splay( getMax(root->left) );
            rightRoot->parent = root;
            root->right = rightRoot;
            
        }
        this->root = root;
        delete temp;
    }
}





SplayNode* Splay::find( int data )
{
    SplayNode *current = root;
    SplayNode *parent = NULL;
    SplayNode *find = NULL;
    
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
            find = current;
            break;
        }
    }
    
    if( find != NULL )
    {
        compare++;
        splay( find );
    }
    else if( parent != NULL )
    {
        compare++;
        find = parent;
        splay( parent );
        cout << data << " was not found in Splay Tree!" << endl;
    }
    
    return find;
}





void Splay::search( int data )
{
    find( data );
}





void Splay::clear( SplayNode *node )
{
    if( node != NULL )
    {
        clear( node->left );
        clear( node->right );
        delete node;
    }
    
    count = 0;
}





void Splay::printTree( SplayNode *root )
{
    if( root != NULL )
    {
        cout << "[" << root->data;
        printTree( root->left );
        
        if( (root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL) )
        {
            cout << "[]";
        }
        
        printTree( root->right );
        cout << "]";
    }
    else
    {
        return;
    }
}





/*****************************************************************************
 *                            private methods                                *
 ****************************************************************************/
void Splay::zig( SplayNode *node)
{
    SplayNode *thisParrent = node->parent;
  
    if (thisParrent->left == node)
    {
        compare++;
        SplayNode *rightChild = node->right;
        
        node->parent = NULL;
        node->right = thisParrent;
        thisParrent->parent = node;
        thisParrent->left = rightChild;
        if (rightChild != NULL)
        {
            compare++;
            rightChild->parent = thisParrent;
        }
    }
    else
    {
        compare++;
        SplayNode *leftChild = node -> left;
        
        node->parent = NULL;
        node->left = thisParrent;
        thisParrent->parent = node;
        thisParrent->right = leftChild;
        
        if (leftChild != NULL) {
            compare++;
            leftChild->parent = thisParrent;
        }
    }
}




void Splay::zigZig( SplayNode *node )
{
    SplayNode *thisParent = node->parent;
    SplayNode *grandParent = thisParent->parent;
    
    
    if (thisParent->left == node)
    {
        compare++;
        SplayNode *rightChild = node->right;
        SplayNode *rightSibling = thisParent->right;
        
        node->parent = grandParent->parent;
        node->right = thisParent;
        
        thisParent->parent = node;
        thisParent->left = rightChild;
        thisParent->right = grandParent;
        
        grandParent->parent = thisParent;
        grandParent->left = rightSibling;
        
        if (node->parent != NULL)
        {
            compare++;
            if (node->parent->left == grandParent)
            {
                node->parent->left = node;
            }
            else
            {
                node->parent->right = node;
            }
        }
        if (rightChild != NULL)
        {
            compare++;
            rightChild->parent = thisParent;
        }
        if (rightSibling != NULL)
        {
            compare++;
            rightSibling->parent = grandParent;
        }
    }
    else
    {
        compare++;
        SplayNode *leftSibling = thisParent->left;
        SplayNode *leftChild = node->left;
        
        node->parent = grandParent->parent;
        node->left = thisParent;
        
        thisParent->parent = node;
        thisParent->left = grandParent;
        thisParent->right = leftChild;
        
        grandParent->parent = thisParent;
        grandParent->right = leftSibling;
        
        if (node->parent != NULL)
        {
            compare++;
            if (node->parent->left == grandParent) {
                node->parent->left = node;
            }
            else
            {
                node->parent->right = node;
            }
        }
        
        
        if (leftChild != NULL)
        {
            compare++;
            leftChild->parent = thisParent;
        }
        
        
        
        if (leftSibling != NULL)
        {
            compare++;
            leftSibling->parent = grandParent;
        }
    }
}





void Splay::zigZag( SplayNode *node )
{
    SplayNode *thisParent = node->parent;
    SplayNode *grandParent= thisParent->parent;
    
    
    if (thisParent->right == node)
    {
        compare++;
        SplayNode *leftChild = node->left;
        SplayNode *rightChild = node->right;
        
        node->parent = grandParent->parent;
        node->left = thisParent;
        node->right = grandParent;
        
        thisParent->parent = node;
        thisParent->right = leftChild;
        
        grandParent->parent = node;
        grandParent->left = rightChild;
        
        if (node->parent != NULL)
        {
            compare++;
            if (node->parent->left == grandParent) {
                compare++;
                node->parent->left = node;
            }
            else {
                compare++;
                node->parent->right = node;
            }
        }
        
        
        if (rightChild != NULL)
        {
            compare++;
            rightChild->parent = grandParent;
        }
        
        
        
        if (leftChild != NULL)
        {
            compare++;
            leftChild->parent = thisParent;
        }
    }
    else
    {
        compare++;
        SplayNode *leftChild = node->left;
        SplayNode *rightChild = node->right;
        
        node->parent = grandParent->parent;
        node->left = grandParent;
        node->right = thisParent;
        
        thisParent->parent = node;
        thisParent->left = rightChild;
        
        grandParent->parent = node;
        grandParent->right = leftChild;
        
        
        
        if (node->parent != NULL)
        {
            compare++;
            if (node->parent->left == grandParent)
            {
                compare++;
                node->parent->left = node;
            }
            else
            {
                compare++;
                node->parent->right = node;
            }
        }
        
        
        if (rightChild != NULL)
        {
            compare++;
            rightChild->parent = thisParent;
        }
        
        
        
        if (leftChild != NULL)
        {
            compare++;
            leftChild->parent = grandParent;
        }
    }
}





SplayNode* Splay::splay( SplayNode *node )
{
    while  (node->parent != NULL )
    {
        compare++;
        SplayNode *thisParent = node->parent;
        SplayNode *grandParent = thisParent->parent;
        
        
        if ( grandParent == NULL )
        {
            compare++;
            zig( node);
        }
        else if ( grandParent->left == thisParent && thisParent->left == node )
        {
            compare+=2;
            zigZig( node );
        }
        else if ( grandParent->right == thisParent && thisParent->right == node )
        {
            compare+=2;
            zigZig( node );
        }
        else
        {
            compare++;
            zigZag( node );
        }
    }
    
    this->root = node;
    
    return node;
}






SplayNode* Splay::getMin( SplayNode *node )
{
    if( node == NULL )
    {
        compare++;
        return NULL;
    }
    else if( node->left == NULL )
    {
        compare++;
        return node;
    }
    else
    {
        compare+=2;
        return getMin(node->left);
    }
}






SplayNode* Splay::getMax( SplayNode *node )
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
        compare+=2;
        return getMax( node->right );
    }
}


#endif /* Splay_h */
