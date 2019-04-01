//
//  SplayNode.h
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#ifndef SplayNode_h
#define SplayNode_h

#include <iostream>

using namespace std;


class SplayNode
{
public:
    SplayNode();
    SplayNode( int data, SplayNode *left, SplayNode *right, SplayNode *parent);
    
    SplayNode *getParent() {return parent;}
    SplayNode *getLeft() {return left;}
    SplayNode *getRight() {return right;}
    
    int getData() {return data;}
    
    friend class Splay;
    
private:
    SplayNode *parent;
    SplayNode *left;
    SplayNode *right;
    
    int data;
    
};




/*****************************************************************************
 *                            constructors                                   *
 ****************************************************************************/
SplayNode::SplayNode()
{
    data = -1;
    left = NULL;
    right = NULL;
    parent = NULL;
}

SplayNode::SplayNode( int data, SplayNode *left, SplayNode *right, SplayNode *parent)
{
    this->data = data;
    this->left = left;
    this->right = right;
    this->parent = parent;
}


#endif /* SplayNode_h */
