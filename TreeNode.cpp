/**
 * @file TreeNode.cpp
 * The implementation file for the TreeNode class.
 * @author Jennifer Coy
 * @date Oct 2016
 */

#include "TreeNode.h"

// default constructor
TreeNode::TreeNode() {
    data = "";              // empty string
    left = nullptr;         // points to nothing
    right = nullptr;         // points to nothing
}

// getter for data
string TreeNode::getData() const {
    return data;
}

// setter for data
void TreeNode::setData(const string newData) {
    data = newData;
}

// getter for left pointer
TreeNode *TreeNode::getLeft() const {
    return left;
}

// getter for right pointer
TreeNode *TreeNode::getRight() const {
    return right;
}

// setter for left pointer
void TreeNode::setLeft(TreeNode *newNext) {
    left = newNext;
}

// setter for right pointer
void TreeNode::setRight(TreeNode *newNext) {
    right = newNext;
}

// a string-based representation of this node
string TreeNode::toString() {
    // print data
    string out_string = "=====\nThis node contains: --" + data + "-- \n";
    // print left child
    if (left != nullptr) {
        out_string += "and points on the left to the node containing: --" + left->getData() + "--\n";
    } else {
        out_string += "and points to nothing on the left.\n";
    }
    // print right child
    if (right != nullptr) {
        out_string += "and points on the right to the node containing: --" + right->getData() + "--\n";
    } else {
        out_string += "and points to nothing on the right.\n";
    }
    // all done -- return result
    return out_string;
}