//
//  main.cpp
//  Project 2
//
//  Created by Eric Hyson on 3/20/19.
//  Copyright © 2019 Eric Hyson. All rights reserved.
//

#include "AVLNode.h"
#include "AVL.h"
#include "BSTNode.h"
#include "BST.h"
#include "SplayNode.h"
#include "Splay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

#include <iostream>

template <typename T>
void readFile( string fileName, T &tree)
{
    
    ifstream inFile;
    
    inFile.open(fileName.c_str());
    
    if( !inFile )
        throw "ERROR: File did not load successfully";
    
    
    
    //INSERT
    int inInt = -1;
    string inLine = "";
    getline( inFile, inLine );
    
    stringstream iStream;
    iStream << inLine;
    
    while( iStream >> inInt )
    {
        tree.insert( inInt );
    }
    
    cout << tree.type  << " tree after insertions: " << endl;
    tree.printTree( tree.getRoot() );
    cout << endl << endl;
    cout << "Comparisons Afer Insertions: " << tree.getCompare() << endl << endl;
    
    
    
    //$
    string money;
    getline( inFile, money );
    
    
    
    //SEARCH
    int searchInt = -1;
    string searchLine = "";
    getline( inFile, searchLine );
    
    stringstream sStream;
    sStream << searchLine;
    
    while( sStream >> searchInt )
    {
        tree.search( searchInt );
    }
    
    cout << "Comparisons After Searches: " << tree.getCompare() << endl << endl;
    
    //$
    string money2;
    getline( inFile, money2 );
    
    
    
    //REMOVE
    int removeInt = -1;
    string removeLine = "";
    getline( inFile, removeLine );
    
    stringstream rStream;
    rStream << removeLine;
    
    while( rStream >> removeInt )
    {
        tree.remove( removeInt );
        cout << tree.type << " tree after removal of " << removeInt << ":" << endl;
        tree.printTree( tree.getRoot() );
        cout << endl << endl;
    }
    
    cout << endl;
    cout << tree.type << " tree after completetion of removals: " << endl;
    tree.printTree( tree.getRoot() );
    cout << endl << endl;
    cout << "Comparisions after removals: " << tree.getCompare() << endl << endl;
    
    inFile.close();
    
    
}



int main(int argc, const char * argv[])
{
    try
    {
        cout << "************************************************************" << endl;
        cout << "*********************BST IMPLEMENTATION*********************" << endl;
        cout << "************************************************************" << endl;
        BST bst;
        readFile(argv[1], bst);
        
        cout << endl << endl << endl << endl;
        cout << "************************************************************" << endl;
        cout << "*********************AVL IMPLEMENTATION*********************" << endl;
        cout <<"************************************************************" << endl;
        AVL avl;
        readFile(argv[1], avl);
        
        cout << endl << endl << endl << endl;
        cout <<"************************************************************" << endl;
        cout <<"*********************SPLAY IMPLEMENTATION*******************" << endl;
        cout <<"************************************************************" << endl;
        Splay splay;
        readFile(argv[1], splay);
        
        cout << endl;
        cout << "Total comparisons for Binary Search Tree: " << bst.getCompare() << endl;
        cout << "Total comparisons for AVL Tree: " << avl.getCompare() << endl;
        cout << "Total comparisons for Splay Tree: " << splay.getCompare() << endl << endl;
        
        
        if( bst.getCompare() < avl.getCompare() && bst.getCompare() < splay.getCompare() )
        {
            cout << "Binary Search Tree is the most efficent!" << endl;
        }
        else if( avl.getCompare() < bst.getCompare() && avl.getCompare() < splay.getCompare() )
        {
            cout << "AVL Tree is the most efficient!" << endl;
        }
        else if(  splay.getCompare() < avl.getCompare() && splay.getCompare() < bst.getCompare() )
        {
            cout << "Splay Tree is the most efficient!" << endl;
        }
        
    }
    catch(...)
    {
        cout << "Unexpected error occured in main... Goodbye. " << endl;
    }
    
    
    
    
    return 0;
}
