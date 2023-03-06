//#include "AvlTree.h"
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

struct TreeNode {
    int value;
    string word;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int avlValue;
};

class AvlTree {

private:

    string type;

    TreeNode *root;
    int avlValue(TreeNode *nodePtr);
    void computeAvlValues(TreeNode *&nodePtr);
    void deleteIntNode(int, TreeNode *&);
    void deleteStringNode(string, TreeNode *&);
    void dodumpIntTree(TreeNode *nodePtr);
    void dodumpStringTree(TreeNode * nodePtr);
    int height(TreeNode *nodePtr);
    void insertIntNode(TreeNode *&, TreeNode *&);
    void insertStringNode(TreeNode *&, TreeNode *&);
    void makeDeletion(TreeNode *&nodePtr);
    bool rightHeavy(TreeNode *nodePtr);
    bool leftHeavy(TreeNode *nodePtr);
    void rotateLeft(TreeNode *&nodePtr);
    void rotateRight(TreeNode *&nodePtr);
    
public:
    AvlTree();
    AvlTree(string name);
    ~AvlTree();

    void dumpIntTree();
    void dumpStringTree();
    void intInsert(int);
    void intRemove(int);
    void intSearch(int, ofstream &);
    void stringInsert(string);
    void stringRemove(string);
    void stringSearch(string, ofstream &);
    int treeHeight();
};

void AvlTree::intRemove(int num) { deleteIntNode(num, root); };

void AvlTree::stringRemove(string word) { deleteStringNode(word, root); };


void AvlTree::dumpIntTree() {
    cout << "---------------------------------" << endl;
    cout << "Root:   " << root << "\n";
    dodumpIntTree(root);
};

void AvlTree::dumpStringTree() {
    cout << "---------------------------------" << endl;
    cout << "Root:   " << root << "\n";
    dodumpStringTree(root);
};

AvlTree::AvlTree(string name) {
    root = NULL;
    type = name;
}

AvlTree::AvlTree() {
    root = NULL;
}

AvlTree::~AvlTree() {
}

//************************************************************************
// Method Name: insertIntNode
//
// Private
//
// Purpose: Inserts a node into a binary tree
//
// Arguments: reference to the root, and a reference to the new node
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::insertIntNode(TreeNode *&nodePtr, TreeNode *&newNode) {

    if (nodePtr == NULL) {
        nodePtr = newNode;
    } else if (newNode->value <= nodePtr->value) {
        newNode->parent = nodePtr;
        insertIntNode(nodePtr->left, newNode);

    } else {
        newNode->parent = nodePtr;
        insertIntNode(nodePtr->right, newNode);
    }
}

//************************************************************************
// Method Name: insertStringNode
//
// Private
//
// Purpose: Inserts a node into a binary tree
//
// Arguments: reference to the root, and a reference to the new node
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::insertStringNode(TreeNode *&nodePtr, TreeNode *&newNode) {

    if (nodePtr == NULL) {
        nodePtr = newNode;
    } else if (newNode->word <= nodePtr->word) {
        newNode->parent = nodePtr;
        insertStringNode(nodePtr->left, newNode);

    } else {
        newNode->parent = nodePtr;
        insertStringNode(nodePtr->right, newNode);
    }
}

//************************************************************************
// Method Name: intInsert
//
// Public
//
// Purpose: Creates a new node and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location.
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::intInsert(int num) {
    TreeNode *newNode;

    newNode = new TreeNode;
    newNode->value = num;
    newNode->avlValue = 0;
    newNode->left = newNode->right = NULL;
    newNode->parent = NULL;
    insertIntNode(root, newNode);
    computeAvlValues(root);
}


// Method Name: stringInsert
//
// Public
//
// Purpose: Creates a new node and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location.
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::stringInsert(string newWord) {
    TreeNode *newNode;

    newNode = new TreeNode;
    newNode->word = newWord;
    newNode->avlValue = 0;
    newNode->left = newNode->right = NULL;
    newNode->parent = NULL;
    insertStringNode(root, newNode);
    computeAvlValues(root);
}

//************************************************************************
// Method Name: intSearch
//
// Public
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: integer to look for, output stream
//
// Returns: none
//*************************************************************************
void AvlTree::intSearch(int num, ofstream & o) {
    TreeNode *nodePtr = root;

    int compareCount = 1;

    while (nodePtr) {
        if (nodePtr->value == num)
        {
          cout << "Found " << num << " after ";
          cout << compareCount << " comparisons using an AVL tree" << endl;
          o << "Found " << num << " after ";
          o << compareCount << " comparisons using an AVL tree" << endl;
          break;
          }
        else if (num < nodePtr->value)
        {
            compareCount++;
            nodePtr = nodePtr->left;
          }
        else
    {
            compareCount++;
            nodePtr = nodePtr->right;
    }
  }

  }

//************************************************************************
// Method Name: stringSearch
//
// Public
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: string to look for, output stream
//
// Returns: number of comparisons to find item
//*************************************************************************
void AvlTree::stringSearch(string newWord, ofstream & o) {
    TreeNode *nodePtr = root;

    int compareCount = 1;

    while (nodePtr) {
        if (nodePtr->word == newWord)
        {
          cout << "Found " << newWord << " after ";
          cout << compareCount << " comparisons using an AVL tree" << endl;
          o << "Found " << newWord << " after ";
          o << compareCount << " comparisons using an AVL tree" << endl;
          break;
          }
        else if (newWord < nodePtr->word)
        {
            nodePtr = nodePtr->left;
            compareCount++;
          }
        else
      {
            nodePtr = nodePtr->right;
            compareCount++;
      }
}

  }

//************************************************************************
// Method Name: deleteIntNode
//
// Private
//
// Purpose: Traverses a binary tree looking for a key value to mark for
//          deletion (could be merged with search).
//
// Arguments: key to delete, nodePtr of the start of the tree (root , subroot, etc.)
//
// Returns: void
//*************************************************************************
void AvlTree::deleteIntNode(int num, TreeNode *&nodePtr) {
    if (nodePtr) {
        if (num < nodePtr->value)
            deleteIntNode(num, nodePtr->left);
        else if (num > nodePtr->value)
            deleteIntNode(num, nodePtr->right);
        else if (nodePtr->value == num)
            makeDeletion(nodePtr);
    } else {
        cout << "Value does not exist!" << endl;
    }
}

//************************************************************************
// Method Name: deleteStringNode
//
// Private
//
// Purpose: Traverses a binary tree looking for a key value to mark for
//          deletion (could be merged with search).
//
// Arguments: key to delete, nodePtr of the start of the tree (root , subroot, etc.)
//
// Returns: void
//*************************************************************************
void AvlTree::deleteStringNode(string newWord, TreeNode *&nodePtr) {
    if (nodePtr) {
        if (newWord < nodePtr->word)
            deleteStringNode(newWord, nodePtr->left);
        else if (newWord > nodePtr->word)
            deleteStringNode(newWord, nodePtr->right);
        else if (nodePtr->word == newWord)
            makeDeletion(nodePtr);
    } else {
        cout << "Value does not exist!" << endl;
    }
}

//************************************************************************
// Method Name: makeDeletion
//
// Private
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of node to be deleted
//
// Returns: void
//*************************************************************************
void AvlTree::makeDeletion(TreeNode *&nodePtr) {
    TreeNode *tempNodePtr;

    if (nodePtr == NULL)
        cout << "Cannot delete empty node.\n";
    else if (nodePtr->right == NULL) {

        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempNodePtr;

    } else if (nodePtr->left == NULL) {

        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;

    } else {
        tempNodePtr = nodePtr->right;
        while (tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
    computeAvlValues(root);
}

//************************************************************************
// Method Name: height
//
// Private
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of the root of the tree (or subtree)
//
// Returns: void
//*************************************************************************
int AvlTree::height(TreeNode *nodePtr) {
    int left_height = 0;
    int right_height = 0;
    if (nodePtr == NULL)
        return 0;
    else {
        left_height = height(nodePtr->left);
        right_height = height(nodePtr->right);
    }
    if (left_height > right_height)
        return 1 + left_height;
    else
        return 1 + right_height;
}

//************************************************************************
// Method Name: treeHeight
//
// Public
//
// Purpose: Public method to call the private height method
//
// Arguments: none
//
// Returns: void
//*************************************************************************
int AvlTree::treeHeight() {
    return height(root);
}

//************************************************************************
// Method Name: avlValue
//
// Private
//
// Purpose: Private method to calculate the avl value of a node.
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
int AvlTree::avlValue(TreeNode *nodePtr) {
    return height(nodePtr->right) - height(nodePtr->left);
}

//************************************************************************
// Method Name: computeAvlValues
//
// Private
//
// Purpose: Private method to calculate the avl values of the entire tree.
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
void AvlTree::computeAvlValues(TreeNode *&nodePtr) {
    if (nodePtr) {
        computeAvlValues(nodePtr->left);
        computeAvlValues(nodePtr->right);
        nodePtr->avlValue = avlValue(nodePtr);
        if (nodePtr->avlValue > 1) {
            rotateLeft(nodePtr);
        } else if (nodePtr->avlValue < -1) {
            rotateRight(nodePtr);
        }
    }
}

//************************************************************************
// Method Name: rotateLeft
//
// Private
//
// Purpose: Private method to perform a left rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
void AvlTree::rotateLeft(TreeNode *&SubRoot) {

    if (leftHeavy(SubRoot->right)) {
        rotateRight(SubRoot->right);
    }

    TreeNode *Temp;

    Temp = SubRoot->right;
    SubRoot->right = Temp->left;
    Temp->left = SubRoot;
    SubRoot = Temp;

    computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: rotateLeft
//
// Private
//
// Purpose: Private method to perform a right rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
void AvlTree::rotateRight(TreeNode *&SubRoot) {
    if (rightHeavy(SubRoot->left)) {
        rotateLeft(SubRoot->left);
    }

    TreeNode *Temp;

    Temp = SubRoot->left;
    SubRoot->left = Temp->right;
    Temp->right = SubRoot;
    SubRoot = Temp;

    computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: dodumpIntTree
//
// Private
//
// Purpose: Private method to show the basic pointer structure of the tree.
//          Initially written to help with debugging.
//
// Arguments: address of a node
//
// Returns: void
// Outputs: tree information
//*************************************************************************
void AvlTree::dodumpIntTree(TreeNode *nodePtr) {
    if (nodePtr) {
        cout << "Add:    " << nodePtr << "\n"
             << "Parent->" << nodePtr->parent << "\n"
             << "Val:    " << nodePtr->value << "\n"
             << "Avl:    " << nodePtr->avlValue << "\n"
             << "Left->  " << nodePtr->left << "\n"
             << "Right-> " << nodePtr->right << "\n\n";

        dodumpIntTree(nodePtr->left);
        dodumpIntTree(nodePtr->right);
    }
}


//************************************************************************
// Method Name: dodumpStringTree
//
// Private
//
// Purpose: Private method to show the basic pointer structure of the tree.
//          Initially written to help with debugging.
//
// Arguments: address of a node
//
// Returns: void
// Outputs: tree information
//*************************************************************************
void AvlTree::dodumpStringTree(TreeNode *nodePtr) {
    if (nodePtr) {
        cout << "Add:    " << nodePtr << "\n"
             << "Parent->" << nodePtr->parent << "\n"
             << "Val:    " << nodePtr->word << "\n"
             << "Avl:    " << nodePtr->avlValue << "\n"
             << "Left->  " << nodePtr->left << "\n"
             << "Right-> " << nodePtr->right << "\n\n";

        dodumpStringTree(nodePtr->left);
        dodumpStringTree(nodePtr->right);
    }
}

//************************************************************************
// Method Name: leftHeavy,rightHeavy
//
// Private
//
// Purpose: Compares the subtrees of a node to see which is taller
//
// Arguments: address of a node
//
// Returns: true if (left/right) heavy
//
//*************************************************************************
bool AvlTree::leftHeavy(TreeNode *nodePtr) {
    return height(nodePtr->left) > height(nodePtr->right);
}

bool AvlTree::rightHeavy(TreeNode *nodePtr) {
    return height(nodePtr->right) > height(nodePtr->left);
}

/**
 *
 */
