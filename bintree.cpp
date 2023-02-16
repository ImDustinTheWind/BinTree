/**********************************************
Name: Dustin Sherer
Coding 08
Purpose: Assignment designed to better understand the
    binary-tree data structure through building one.
**********************************************/

#include "bintree.h"


BinTree::BinTree() {
    root = NULL;
}

BinTree::~BinTree() {
    clear();
}

//**************************************************
// non-overloaded public methods
//**************************************************
bool BinTree::isEmpty() {
    return (root == NULL);
}

int BinTree::getCount() {
    return count;
}

bool BinTree::getRootData(Data* rootData) {
    bool isSuccess = false; 
    if (root) {
        rootData->id = root->data.id;
        rootData->information = root->data.information;
        isSuccess = true;
    }
    else { rootData->id = -1; }
    return isSuccess;
}

void BinTree::displayTree() {
    std::cout << "DISPLAY TREE\n";
    std::cout << "==============================================\n";
    if (isEmpty()) {
        std::cout << "Tree is empty\n";
    }
    else { std::cout << "Tree is NOT empty\n"; }
    std::cout << "Height " << getHeight() << std::endl;
    std::cout << "Node count: " << getCount() << std::endl;
    std::cout << "\nPre-Order Traversal\n";
    displayPreOrder();
    std::cout << "\nIn-Order Traversal\n";
    displayInOrder();
    std::cout << "\nPost-Order Traversal\n";
    displayPostOrder();
    std::cout << "==============================================\n\n";
    return;
}

//**************************************************
// non-overloaded private methods
//**************************************************

DataNode* BinTree::minValueNode(DataNode* node) {
    DataNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

//**************************************************
// overloaded public/private method - clear()
//**************************************************
void BinTree::clear() {
    clear(root);
    root = NULL;
    count = 0;
}

void BinTree::clear(DataNode* temproot) {
    if (temproot) {
        clear(temproot->left);
        clear(temproot->right);
        temproot->left = NULL;
        temproot->right = NULL;
        delete temproot;
    }
    return;
}

//**************************************************
// overloaded public/private method - addNode()
//**************************************************
bool BinTree::addNode(int id, const std::string* info) {
    bool isSuccess = false;
    if (id > 0 && info != NULL) {
        DataNode* newNode = new DataNode;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->data.id = id;
        newNode->data.information = *info;
        isSuccess = addNode(newNode, &root);
        count++;
    }
    return isSuccess;
}

bool BinTree::addNode(DataNode* newNode, DataNode** temproot) {
    bool isSuccess = false;
    if (!(*temproot)) {
        *temproot = newNode;
        isSuccess = true;
    }
    else {
        if (newNode->data.id < ((*temproot)->data.id)) {
            isSuccess = addNode(newNode, &((*temproot)->left));
        }
        else {
            isSuccess = addNode(newNode, &((*temproot)->right));
        }
    }
    return isSuccess;
}

//**************************************************
// overloaded public/private method - removeNode()
//**************************************************
bool BinTree::removeNode(int searchId) {
    bool isSuccess = false;
    int tempcount = count;
    root = removeNode(searchId, root);
    if (count < tempcount) {
        isSuccess = true;
    }
    return isSuccess;
}

DataNode* BinTree::removeNode(int searchId, DataNode* temproot) {
    if (temproot) {
        if (searchId < temproot->data.id) {
            temproot->left = removeNode(searchId, temproot->left);
        }
        else if (searchId > temproot->data.id) {
            temproot->right = removeNode(searchId, temproot->right);
        }
        else {
            DataNode* tempnode = new DataNode;
            if (temproot->left == NULL) {
                tempnode = temproot->right;
                delete temproot;
                temproot = tempnode;
                count--;
            }
            else if (temproot->right == NULL) {
                tempnode = temproot->left;
                delete temproot;
                temproot = tempnode;
                count--;
            }
            else {
                tempnode = minValueNode(temproot->right);
                temproot->data.id = tempnode->data.id;
                temproot->data.information = tempnode->data.information;
                temproot->right = removeNode(tempnode->data.id, temproot->right);
            }
        }
    }
    return temproot;
}

//**************************************************
// overloaded public/private method - getNode()
//**************************************************
bool BinTree::getNode(Data* passData, int id) {
    bool isSuccess = false;
    if (id > 0) {
        isSuccess = getNode(passData, id, root);
    }
    return isSuccess;
}

bool BinTree::getNode(Data* passData, int searchId, DataNode* temproot) {
    bool isSuccess = false;
    if (temproot && searchId == temproot->data.id) {
        passData->id = temproot->data.id;
        passData->information = temproot->data.information;
        isSuccess = true;
    }
    else if (temproot) {
        if (searchId < temproot->data.id) {
            isSuccess = getNode(passData, searchId, temproot->left);
        }
        else {
            isSuccess = getNode(passData, searchId, temproot->right);
        }
    }
    return isSuccess;
}

//**************************************************
// overloaded public/private method - contains()
//**************************************************
bool BinTree::contains(int searchId) {
    bool isValid = false;
    if (searchId > 0) {
        isValid = contains(searchId, root);
    }
    return isValid;
}

bool BinTree::contains(int searchId, DataNode* temproot) {
    bool hasId = false;
    if (temproot && temproot->data.id == searchId) {
        hasId = true;
    }
    else if (temproot) {
        if (searchId < temproot->data.id) {
            hasId = contains(searchId, temproot->left);
        }
        else {
            hasId = contains(searchId, temproot->right);
        }
    }
    return hasId;
}

//**************************************************
// overloaded public/private method - getHeight()
//**************************************************
int BinTree::getHeight() {
    return getHeight(root);
}

int BinTree::getHeight(DataNode* temproot) {
    int height = 0;
    if (temproot) {
        int left = 0;
        int right = 0;
        left += getHeight(temproot->left);
        right += getHeight(temproot->right);
        if (left >= right) {
            height += left;
        }
        else { height += right; }
        height++;
    }
    return height;
}

//**************************************************
// overloaded public/private method - displayPreOrder()
//**************************************************
void BinTree::displayPreOrder() {
    displayPreOrder(root);
}

void BinTree::displayPreOrder(DataNode* temproot) {
    if (temproot) {
        std::cout << temproot->data.id << " " << temproot->data.information << std::endl;
        displayPreOrder(temproot->left);
        displayPreOrder(temproot->right);
    }
}

//**************************************************
// overloaded public/private method - displayPostOrder()
//**************************************************
void BinTree::displayPostOrder() {
    displayPostOrder(root);
}

void BinTree::displayPostOrder(DataNode* temproot) {
    if (temproot) {
        displayPostOrder(temproot->left);
        displayPostOrder(temproot->right);
        std::cout << temproot->data.id << " " << temproot->data.information << std::endl;
    }
}

//**************************************************
// overloaded public/private method - displayInOrder()
//**************************************************
void BinTree::displayInOrder() {
    displayInOrder(root);
}

void BinTree::displayInOrder(DataNode* temproot) {
    if (temproot) {
        displayInOrder(temproot->left);
        std::cout << temproot->data.id << " " << temproot->data.information << std::endl;
        displayInOrder(temproot->right);
    }
    return;
}
