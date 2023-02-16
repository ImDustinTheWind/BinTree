/**********************************************
Name: Dustin Sherer
Coding 08
Purpose: Assignment designed to better understand the
    binary-tree data structure through building one.
**********************************************/

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include "data.h"

#include <iostream>
#include <string>

class BinTree {
public:

    BinTree();
    ~BinTree();

    bool isEmpty();
    int getCount();
    bool getRootData(Data*);
    void displayTree();

    void clear();
    bool addNode(int, const std::string*);
    bool removeNode(int);
    bool getNode(Data*, int);
    bool contains(int);
    int getHeight();

    void displayPreOrder();
    void displayPostOrder();
    void displayInOrder();

private:

    DataNode* minValueNode(DataNode*);

    void clear(DataNode*);
    bool addNode(DataNode*, DataNode**);
    DataNode* removeNode(int, DataNode*);
    bool getNode(Data*, int, DataNode*);
    bool contains(int, DataNode*);
    int getHeight(DataNode*);

    void displayPreOrder(DataNode*);
    void displayPostOrder(DataNode*);
    void displayInOrder(DataNode*);

    DataNode* root;
    int count = 0;

};


#endif /* BINTREE_BINTREE_H */

