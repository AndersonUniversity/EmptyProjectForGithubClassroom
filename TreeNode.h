/**
 * @file TreeNode.h
 * A class to represent the node of a binary tree, with left and right pointers.
 * @author Jennifer Coy
 * @date Oct 2016
 */

#ifndef TREENODE_H
#define TREENODE_H

#include <string>
using namespace std;

/**
 * A class representing a node in a binary tree.
 */
class TreeNode {
private:
    /** the information stored in this node */
    string data = "";
    /** a link to the left child node */
    TreeNode* left;
    /** a link to the right child node */
    TreeNode* right;

public:
    /**
     * constructor for a default (empty) node
     */
    TreeNode();

    /**
     * Getter for data
     * @return a string representing the data
     */
    string getData() const;

    /**
     * Setter for data
     * @param data the new data to include in the string
     */
    void setData(const string data);

    /**
     * Getter for the left child
     * @return a pointer to the left node
     */
    TreeNode *getLeft() const;

    /**
     * Getter for the right child
     * @return a pointer to the right node
     */
    TreeNode *getRight() const;

    /**
     * Setter for the left child
     * @param next pointer to the left child
     */
    void setLeft(TreeNode *next);

    /**
     * Setter for the right child
     * @param next pointer to the right child
     */
    void setRight(TreeNode *next);

    /**
     * A string-based representation of this node
     * @return a string that represents this node
     */
    string toString();
};
#endif //TREENODE_H
