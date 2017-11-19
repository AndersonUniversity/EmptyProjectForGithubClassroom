/**
 * @file BinarySearchTree.cpp
 * A linked implementation of the Binary Search Tree
 * @author Jennifer Coy
 * @date November 2016
 */

#include "BinarySearchTree.h"
#include <iostream>
#define DEBUG true      // used for debugging the destructor
using namespace std;

// Default constructor, initialize empty tree
BinarySearchTree::BinarySearchTree() {
    // set root equal to nullptr
    root = nullptr;
}

// Default destrutor, free all memory used in the tree
BinarySearchTree::~BinarySearchTree() {
    TreeNode* thisNode = nullptr;           // current node in traversal


    // start at root
    thisNode = root;

    // do a postorder tree traversal with delete
    postorderDelete(root);

    // reset root to nullptr
    root = nullptr;
    //if (DEBUG) cout << "Tree is now empty." << endl;

    // we are done with this recursive function
    return;

}

// Determine if the tree is empty.
bool BinarySearchTree::isEmpty() const {
    if (root == nullptr) { // no nodes in tree, so return true
        return true;
    } else { // there is at least one node in the tree
        return false;
    }
}

// Search for a node and set the pointers for the node itself, and it's parent.
// Used by insertNode, deleteNode, fetchNode and indirectly by updateNode
// key is the item we are searching for
// node will be a pointer to the node containing that item (or nullptr if not found)
// parent will be a pointer to the parent of the node (or nullptr)
void BinarySearchTree::findNode(string key, TreeNode*& node, TreeNode*& parent) const {
    // start at the root
    node = root;
    parent = nullptr;  // parent is null until we make the first move left or right

    // loop through the tree, until we find it (or not)
    while (node != nullptr) {
        // is this node the one we are looking for?
        if (node->getData() == key) {  // yup!  we found it
            // note that in the special case of the key being in the first node,
            // we'll have parent == nullptr
            // node and parent are already set, so we are ok.
            return;
        } else { // nope, move to the next one
            // set parent to this node
            parent = node;
            // move to the next one, either left or right
            if (key < node->getData()) {
                // move left
                node = node->getLeft();
            } else {
                // move right
                node = node->getRight();
            }
            // note that if we've reached the end of this branch without finding
            // anything, we'll have node = nullptr and parent = leaf
        }
    }
    // NOTE:  in the case of an empty tree, with root == nullptr,
    // this function returns node == nullptr and parent == nullptr
}

// Insert a new node (will create a new TreeNode), following the Binary
// Search Tree rules.
// NOTE:  *& means "pass address by reference" so we can change the value of node/parent
//        * to point to where we want, and they can be accessed back in main.
void BinarySearchTree::insertNode(string newData) throw(logic_error) {
    TreeNode* newNode = nullptr;       // pointer to the new node
    TreeNode* searchNode = nullptr;    // used with findNode to find where this one goes
    TreeNode* parentNode = nullptr;    // used with findNode to find where this one goes

    // create node and fill the new node with data
    newNode = new TreeNode();
    newNode->setData(newData);

    // find where this node belongs in the tree by doing a search for it
    findNode(newData, searchNode, parentNode);

    // searchNode should be null, otherwise we have a duplicate -- throw an error
    if (searchNode != nullptr) {
        throw logic_error("Error -- cannot insert a duplicate node in a Binary Search Tree.");
    } else { // the search was successful, and parentNode will be the parent for this node
        // special case -- if the tree is empty, prentNode will be nullptr
        if (parentNode == nullptr) {
            // the new node *is* the root
            root = newNode;
        }
        // otherwise, figure if newNode should be a left or right child of this parentNode
        else if (newData < parentNode->getData()) {
            // insert on left
            parentNode->setLeft(newNode);
        } else {
            // insert on right
            parentNode->setRight(newNode);
        }
    }
}

// Remove and return the contents of a node, or NOT_FOUND_MESSAGE, restructuring the tree
// according to the Binary Search Tree rules.
string BinarySearchTree::deleteNode(string key) {
    TreeNode* searchNode = nullptr;    // used with findNode to find the target node
    TreeNode* parentNode = nullptr;    // parent of the target node
    TreeNode* tempPtr = nullptr;       // used if the deleted node has two children
    TreeNode* tempParent = nullptr;    // used if the deleted node has two children
    string returnValue = "";           // value to return
    bool rootFlag = false;             // true if we are deleting the root node

    // find the node to be deleted
    findNode(key, searchNode, parentNode);

    // if node is not present, return NOT_FOUND_MESSAGE
    if (searchNode == nullptr) {
        return NOT_FOUND_MESSAGE;
    }

    // store data so we can return it
    returnValue = searchNode->getData();

    // if the node is a root, then we have a special case!
    if (searchNode == root) {
        rootFlag = true;
    }

    // determine how to delete this node, based on number of children
    if (searchNode->getLeft() == nullptr && searchNode->getRight() == nullptr) {
        /////// this node is just a leaf ///////
        // handle special case of root
        if (rootFlag == true) {
            root = nullptr; // no nodes in the tree
        } else if (parentNode->getLeft() == searchNode) {
            // if the node to delete is the left child of the parent, then
            // need to set that left pointer to null
            parentNode->setLeft(nullptr);
        } else {
            // searchNode must be on the right side of the parent
            parentNode->setRight(nullptr);
        }
        // delete the node
        delete(searchNode);
        searchNode = nullptr;
    } else if (searchNode->getLeft() != nullptr && searchNode->getRight() == nullptr)
    {   /////// if there is only a left child of searchNode... /////
        // handle special case of root
        if (rootFlag == true) {
            root = searchNode->getLeft(); // root node is now left child
        } else if (parentNode->getLeft() == searchNode) {
            // if the node to delete is the left child of the parent, then
            // connect SearchNode's child to the left side of parent node
            parentNode->setLeft(searchNode->getLeft());
        } else {
            // searchNode must be on the right side of the parent
            parentNode->setRight(searchNode->getLeft());
        }
        // now we can delete this node
        delete(searchNode);
        searchNode = nullptr;

    } else if (searchNode->getLeft() == nullptr && searchNode->getRight() != nullptr) {
        /////// if there is only a right child of searchNode... /////
        // handle special case of root
        if (rootFlag == true) {
            root = searchNode->getRight(); // root node is now right child
        } else if (parentNode->getLeft() == searchNode) {
            // if the node to delete is the left child, then
            // connect to the left side of parent node
            parentNode->setLeft(searchNode->getRight());
        } else {
            // searchNode must be on the right side of the parent
            parentNode->setRight(searchNode->getRight());
        }
        // now we can delete this node
        delete(searchNode);
        searchNode = nullptr;
    } else {
        // if the node has two children, find the deleted node’s LEFT descendant that has the LARGEST
        // value, then move that node to where the deleted node is
        // (Note -- no need for special case for root node here, since we aren't deleting it, just copying)

        // use tempPtr and tempParent to move to left child of searchNode
        tempPtr = searchNode->getLeft();
        tempParent = searchNode;
        // now move tempPtr all the way to the right most leaf
        while (tempPtr->getRight() != nullptr) {
            tempParent = tempPtr;
            tempPtr = tempPtr->getRight();
        }
        // now tempPtr points to a leaf, and tempParent is the leaf's parent
        // we want the contents of this leaf to move to where searchNode is
        searchNode->setData(tempPtr->getData());
        // now, instead of deleting searchNode, we delete this leaf!
        // need to determine if we are deleting a left or right child of tempParent
        if (tempParent->getLeft() == tempPtr) {
            // tempPtr is the left child
            tempParent->setLeft(nullptr);
        } else {
            // tempPtr is the right child
            tempParent->setRight(nullptr);
        }
        // now delete it
        delete(tempPtr);
        tempPtr = nullptr;
    }

    // return the data
    return returnValue;
}

// Search for and return the contents of a node, or NOT_FOUND_MESSAGE.
string BinarySearchTree::fetchNode(string key) const {
    // need temp pointers for the node and the parent node
    TreeNode* targetNode = nullptr;         // will point to the node we want
    TreeNode* parentNode = nullptr;         // will poitn to the parent node (we don't use this here)

    // search for the node using findNode
    findNode(key, targetNode, parentNode);

    // if we find it, return the targetNode's key
    if (targetNode != nullptr) {
        return targetNode->getData();
    } else {
        return NOT_FOUND_MESSAGE;
    }
}

// Search for the old contents, remove it, then add the new contents.
// Implemented as a delete followed by an insert.  TODO:  should throw
// an exception if we can't find the old contents
void BinarySearchTree::updateNode(string oldContents, string newContents) {
    // delete the old one
    deleteNode(oldContents);
    // add the new one
    insertNode(newContents);
}

// Conduct an inorder traversal, starting from root
string BinarySearchTree::inorderTraversal() const {
    string outString = "";      // output string

    // conduct the traversal, using a private method (needed because we
    // need to pass root, which is private
    inorder(root, outString);

    // return the result
    return outString;
}

// Conduct an preorder traversal, starting from root
string BinarySearchTree::preorderTraversal() const {
    string outString = "";      // output string

    // conduct the traversal, using a private method (needed because we
    // need to pass root, which is private
    preorder(root, outString);

    // return the result
    return outString;
}

// Conduct an postorder traversal, starting from root
string BinarySearchTree::postorderTraversal() const {
    string outString = "";      // output string

    // conduct the traversal, using a private method (needed because we
    // need to pass root, which is private
    postorder(root, outString);

    // return the result
    return outString;
}

// return the count of the number of nodes in the tree
int BinarySearchTree::countNodes() const {
    int numNodes = 0;      // number of nodes

    // conduct the traversal, using a private method (needed because we
    // need to pass root, which is private
    count(root, numNodes);

    // return the result
    return numNodes;
}

// Perform an in order traversal, filling the_array as we go
void BinarySearchTree::inorderTraversalFillArray(string the_array[], int size) throw(logic_error) {
    int index = 0;              // need a place to store the next index
    // check to make sure we have the same number of nodes in the tree as we expect to have in the array
    if (size != countNodes()) {
        throw logic_error("Fatal error in Binary Search Tree sort.");
    }

    inorderFillArray(root, the_array, index);
}

// In order tree traversal, appending the contents to a string to be returned.
// NOTE:  Need to have & so that we can change outString
void BinarySearchTree::inorder(TreeNode* thisNode, string& outString) const {
    // if this is a nullptr, return (should not happen, but want to avoid it!)
    if (thisNode == nullptr) {
        outString += "Oops - inorder reached nullptr";
        return;
    }
    // move Left
    if (thisNode->getLeft() != nullptr) {
        inorder(thisNode->getLeft(), outString);
    }
    // visit
    outString += thisNode->getData() + "\t";
    // move right
    if (thisNode->getRight() != nullptr) {
        inorder(thisNode->getRight(), outString);
    }
    // we are done with this recursive function
    return;
}

// Pre order tree traversal, appending the contents to a string to be returned.
void BinarySearchTree::preorder(TreeNode* thisNode, string& outString) const {
    // if this is a nullptr, return (should not happen, but want to avoid it!)
    if (thisNode == nullptr) {
        outString += "Oops - inorder reached nullptr";
        return;
    }

    // visit
    outString += "[" + thisNode->getData() + "] ";
    // move Left
    if (thisNode->getLeft() != nullptr) {
        preorder(thisNode->getLeft(), outString);
    }
    // move right
    if (thisNode->getRight() != nullptr) {
        preorder(thisNode->getRight(), outString);
    }
    // we are done with this recursive function
    return;
}

// Post order tree traversal, appending the contents to a string to be returned.
void BinarySearchTree::postorder(TreeNode* thisNode, string& outString) const {
    // if this is a nullptr, return (should not happen, but want to avoid it!)
    if (thisNode == nullptr) {
        outString += "Oops - inorder reached nullptr";
        return;
    }

    // move Left
    if (thisNode->getLeft() != nullptr) {
        postorder(thisNode->getLeft(), outString);
    }
    // move right
    if (thisNode->getRight() != nullptr) {
        postorder(thisNode->getRight(), outString);
    }
    // visit
    outString += "[" + thisNode->getData() + "] ";

    // we are done with this recursive function
    return;
}

// recursively delete nodes in a post order traversal
void BinarySearchTree::postorderDelete(TreeNode* thisNode) {
    // if this is a nullptr, root is null
    if (thisNode == nullptr) {
        if (DEBUG) cout << "deleted an empty tree" << endl;
        return;
    }

    // move Left
    if (thisNode->getLeft() != nullptr) {
        postorderDelete(thisNode->getLeft());
    }
    // move right
    if (thisNode->getRight() != nullptr) {
        postorderDelete(thisNode->getRight());
    }
    // visit by deleting the node
    //if (DEBUG) cout << "Deleting [" + thisNode->getData() + "]..." << endl;
    delete(thisNode);
    thisNode = nullptr;

    // we are done with this recursive function
    return;

}

// recursively count the number of nodes
void BinarySearchTree::count(TreeNode* thisNode, int& numNodes) const {
    // if this is a nullptr, just quit
    if (thisNode == nullptr) {
        return;
    }

    // move Left
    if (thisNode->getLeft() != nullptr) {
        count(thisNode->getLeft(), numNodes);
    }
    // move right
    if (thisNode->getRight() != nullptr) {
        count(thisNode->getRight(), numNodes);
    }
    // visit by counting this node
    numNodes++;

    // we are done with this recursive function
    return;

}

// recursively insert Node contents into the array
void BinarySearchTree::inorderFillArray(TreeNode* thisNode, string the_array[], int& next_index) {
    // if this is a nullptr, return (should not happen, but want to avoid it!)
    if (thisNode == nullptr) {
        return;
    }
    // move Left
    if (thisNode->getLeft() != nullptr) {
        inorderFillArray(thisNode->getLeft(), the_array, next_index);
    }
    // visit
    the_array[next_index] = thisNode->getData();
    next_index++;
    // move right
    if (thisNode->getRight() != nullptr) {
        inorderFillArray(thisNode->getRight(), the_array, next_index);
    }
    // we are done with this recursive function
    return;
}