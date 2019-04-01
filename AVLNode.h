//
//  AVLNode.h
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#ifndef AVLNode_h
#define AVLNode_h
#include <iostream>

using namespace std;

class AVLNode
{
public:
    AVLNode();
    AVLNode(  AVLNode *left, AVLNode *right, int data, int height, int balance );
    
    AVLNode *getLeft();
    AVLNode *getRight();
    
    int getData() {return data;}
    int getHeight( AVLNode *node );
    int getBalance( AVLNode *node );
    
    friend class AVL;

private:
    class AVLNode *left;
    class AVLNode *right;
    
    int data;
    int height;
    int balance;
    
};



/*****************************************************************************
 *                            constructors                                   *
 ****************************************************************************/
AVLNode::AVLNode()
{
    left = NULL;
    right = NULL;
    data = -1;
    height = 0;
    balance = 0;
}


AVLNode::AVLNode( AVLNode *left, AVLNode *right, int data, int height, int balance )
{
    this->left = left;
    this->right = right;
    this->data = data;
    this->height = height;
    this->balance = balance;
}


/*****************************************************************************
 *                            public methods                                 *
 ****************************************************************************/
AVLNode* AVLNode::getRight()
{
    if( right == NULL )
        return 0;
    else
        return right;
}




AVLNode* AVLNode::getLeft()
{
    if( left == NULL )
        return 0;
    else
        return left;
}





int AVLNode::getHeight( AVLNode *node )
{
    return node == NULL ? -1 : node->height;
}





int AVLNode::getBalance( AVLNode *node )
{
    if( node == NULL )
    {
        return 0;
    }
    else
    {
        return ( node->getHeight( node->getRight()) - node->getHeight( node->getLeft()) );
    }
}


#endif /* AVLNode_h */
