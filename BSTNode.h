//
//  BSTNode.h
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#ifndef BSTNode_h
#define BSTNode_h

#include <iostream>

using namespace std;


class BSTNode
{
public:
    BSTNode();
    BSTNode( int data, BSTNode *left, BSTNode *right );
    
    int data;
    
    BSTNode *right;
    BSTNode *left;
    
    friend class BST;
    
};



/*****************************************************************************
 *                            constructors                                   *
 ****************************************************************************/
BSTNode::BSTNode()
{
    data = -1;
    right = NULL;
    left = NULL;
}





BSTNode::BSTNode( int data, BSTNode *left, BSTNode *right )
{
    this->data = data;
    this->left = left;
    this->right = right;
}


#endif /* BSTNode_h */
