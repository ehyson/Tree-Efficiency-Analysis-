//
//  AVL.h
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#ifndef AVL_h
#define AVL_h

#include "AVLNode.h"
#include <iostream>

using namespace std;


class AVL
{
public:
    AVL();
    ~AVL();
    AVLNode *getRoot() {return root;}
    
    
    int getCount() {return count;}
    int getCompare() {return compare;}
    int treeHeight( AVLNode *node );
    int getBalance( AVLNode* node);
    int max( int left, int right );
    
    void insert( int data );
    void remove( int data );
    void search( int data );
    void clear( AVLNode *node );
    void printTree( AVLNode *node );
    
    bool isEmpty() const {return root == NULL;}
    
    string type = "AVL";

private:
    int count;
    int compare;
    AVLNode *root;
    
    AVLNode *insert( AVLNode* &node, int data );
    AVLNode *getMin( AVLNode *node );
    AVLNode *getMax( AVLNode *node );
    
    void remove( AVLNode* &node, int &data );
    void balance( AVLNode* &node);
    
    void singleRotateLeft( AVLNode* &node );
    void singleRotateRight( AVLNode* &node );
    void doubleRotateLeft( AVLNode* &node );
    void doubleRotateRight( AVLNode* &node );
    
};




/*****************************************************************************
 *                            constructors                                   *
 ****************************************************************************/
AVL::AVL()
{
    root = NULL;
    count = 0;
    compare = 0;
}





AVL::~AVL()
{
    this->clear(root);
    count = 0;
    compare = 0;
}





/*****************************************************************************
 *                            public methods                                 *
 ****************************************************************************/
void AVL::insert( int data )
{
    if( isEmpty() )
    {
        AVLNode *iNode = new AVLNode();
        iNode->data = data;
        this->root = iNode;
        count++;
        return;
    }
        insert( root, data );
}





void AVL::remove( int data )
{
    remove( root, data );
}





int AVL::max( int left, int right )
{
    if( left > right )
    {
        return left;
    }
    else
    {
        return right;
    }
}





int AVL::treeHeight( AVLNode *node )
{
    int height = 0;
    
    if( node != NULL )
    {
        compare++;
        int leftHeight = treeHeight( node->left );
        int rightHeight = treeHeight( node->right );
        
        height = max( leftHeight, rightHeight ) +1;
    }
    
    return height;
}





int AVL::getBalance( AVLNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return node->getHeight(node->getRight()) - node->getHeight(node->getLeft());
    }
}





void AVL::clear( AVLNode *node )
{
    if( node != NULL )
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
    count = 0;
}





void AVL::search( int data )
{
    bool found = false;
    AVLNode *current = root;
    AVLNode *parent;
    
    while( current != NULL )
    {
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
        cout << data << " was not found in AVL Tree!" << endl;
    }
}





void AVL::printTree( AVLNode *node )
{
    if( node == NULL )
    {
        return;
    }
    else
    {
        cout << "[" << node->data;
        printTree( node->left );
        
        if( (node->right != NULL && node->left == NULL) || (node->right == NULL && node->left != NULL) )
        {
            cout << "[]";
        }
        
        printTree( node->right );
        cout << "]";
    }
    
}





/*****************************************************************************
 *                            private methods                                *
 ****************************************************************************/

AVLNode* AVL::insert( AVLNode* &node, int data )
{
    if( node == NULL )
    {
        node = new AVLNode();
        node->data = data;
        count++;
        compare++;
        return node;
    }
    else if( data < node->data )
    {
        compare++;
        node->left = insert( node->left, data );
        
    }
    else if( data > node->data )
    {
        compare++;
        node->right = insert( node->right, data );
    }
    else
    {
        compare++;
        return node;
    }
    
    
    node->height = max( treeHeight(node->left), treeHeight(node->right) );
    node->balance = getBalance( node );
    balance( node );
    
    return node;
}






AVLNode* AVL::getMin( AVLNode *node )
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
        compare++;
        return getMin( node->left );
    }
}





AVLNode* AVL::getMax( AVLNode *node )
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





void AVL::remove( AVLNode* &node, int &data )
{
    if( node == NULL )
    {
        compare++;
        cout <<  data << " was not found in AVL tree!" << endl;
        return;
    }
    
    
    if( data < node->data )
    {
        compare++;
        remove( node->left, data );
    }
    else if( data > node->data )
    {
        compare++;
        remove( node->right, data );
    }
    else if( node->right != NULL && node->left != NULL )
    {
        compare+=2;
        node->data = getMin(node->right)->data;
        remove( node->right, node->data );
    }
    else
    {
        AVLNode *delNode = node;
        node = (node->left != NULL) ? node->left : node->right;
        compare++;
        count--;
        delete delNode;
        
    }
    
    
    if( node != NULL )
    {
        compare++;
        node->height = max( treeHeight(node->left), treeHeight(node->right) );
        node->balance = getBalance( node );
    }
    
    balance( node );
    
}





void AVL::balance( AVLNode* &node)
{
    static const int MIN_BALANCE = 1;
    
    if ( node == NULL )
    {
        compare++;
        return;
    }
    
    
    if ( node->balance < -MIN_BALANCE )
    {
        
        if (treeHeight(node->left->left) >= treeHeight(node->left->right))
        {
            compare++;
            singleRotateLeft( node);
        }
        else
        {
            compare++;
            doubleRotateLeft( node );
        }
    }
    else
    {
        if( node->balance > MIN_BALANCE )
        {
            
            if (treeHeight(node->right->right) >= treeHeight(node->right->left))
            {
                
                compare++;
                singleRotateRight( node );
            }
            else
            {
                compare++;
                doubleRotateRight( node );
            }
        }
    }
    
    node->height = max( treeHeight(node->left), treeHeight(node->right) );
}
    
    



void AVL::singleRotateLeft( AVLNode* &node )
{
    
    AVLNode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    
    node->height = max( treeHeight(node->left), treeHeight(node->right) );
    temp->height = max( treeHeight(temp->left), treeHeight(temp->right) );
    node = temp;
   
}






void AVL::singleRotateRight( AVLNode* &node )
{
    AVLNode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    
   
    
    node->height = max( treeHeight(node->left), treeHeight(node->right) );
    temp->height = max( treeHeight(temp->left), treeHeight(temp->right) );
    node = temp;
   
}





void AVL::doubleRotateLeft( AVLNode* &node )
{
    singleRotateRight( node->left );
    singleRotateLeft( node );
}





void AVL::doubleRotateRight( AVLNode* &node )
{
    singleRotateLeft( node->right );
    singleRotateRight( node );
}


#endif /* AVL_h */
