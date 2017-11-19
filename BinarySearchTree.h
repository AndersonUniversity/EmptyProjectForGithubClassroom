/**
 * @file BinarySearchTree.h
 * A linked implementation of the Binary Search Tree
 * @author Jennifer Coy
 * @date November 2016
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <stdexcept>

class BinarySearchTree {

private:
    TreeNode *root;             // the beginning node of the tree
    const string NOT_FOUND_MESSAGE = "Did not locate node in tree."; // returned by findNode if not found

public:
    /**
     * Default constructor, initialize empty tree
     */
    BinarySearchTree();

    /**
     * Default destrutor, free all memory used in the tree
     */
    ~BinarySearchTree();

    /**
     * Determine if the tree is empty.
     * @return true if the tree is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * Search for a node and set the pointers for the node itself, and it's parent.
     * Used by insertNode, deleteNode, fetchNode and indirectly by updateNode.
     * NOTE:  *& means "pass address by reference" so we can change the value of node/parent
     * to point to where we want, and they can be accessed back in main.
     * @param key the item we are searching for
     * @param node a pointer to the node containing that item (or nullptr if not found)
     * @param parent a pointer to the parent of the node (or nullptr)
     */
    void findNode(string key, TreeNode*& node, TreeNode*& parent) const;

    /**
     * Insert a new node (will create a new TreeNode), following the Binary
     * Search Tree rules.
     * @param newData the information to insert into the node
     * @throws a logic_error if a duplicate node is inserted
     */
    void insertNode(string newData) throw(logic_error);

    /**
     * Remove and return the contents of a node, restructuring the tree
     * according to the Binary Search Tree rules.
     * @param key the identifying information for the node to delete
     * @return the contents of a node, or NOT_FOUND_MESSAGE
     */
    string deleteNode(string key);

    /**
     * Search for and return the contents of a node.
     * @param key the item to search for
     * @return the contents of the node (currently just the key), or NOT_FOUND_MESSAGE
     */
    string fetchNode(string key) const;

    /**
     * Search for the old contents, remove it, then add the new contents.
     * Implemented as a delete followed by an insert.  TODO:  should throw
     * an exception if we can't find the old contents
     * @param oldContents the item to remove
     * @param newContents the item to add
     */
    void updateNode(string oldContents, string newContents);

    /**
     * Conduct an inorder traversal, starting from root
     * @return a string containing the contents of the nodes
     */
    string inorderTraversal() const;

    /**
     * Conduct an preorder traversal, starting from root
     * @return a string containing the contents of the nodes
     */
    string preorderTraversal() const;

    /**
     * Conduct an postorder traversal, starting from root
     * @return a string containing the contents of the nodes
     */
    string postorderTraversal() const;

    /**
     * Count the number of nodes in the tree
     * @return the total number of nodes
     */
    int countNodes() const;

    /**
     * Perform an in order traversal, filling the_array as we go
     * @param the_array the array to place the Node contents into
     * @param size the number of items in the array
     */
    void inorderTraversalFillArray(string the_array[], int size) throw(logic_error) ;

private:

    /**
     * In order tree traversal, appending the contents to a string to be returned.
     * NOTE:  Need to have & so that we can change outString
     * @return a string containing the contents in an indorder traversal order
     */
    void inorder(TreeNode* thisNode, string& outString) const;

    /**
     * Pre order tree traversal, appending the contents to a string to be returned.
     * @return a string containing the contents in an preorder traversal order
     */
    void preorder(TreeNode* thisNode, string& outString) const;

    /**
     * Post order tree traversal, appending the contents to a string to be returned.
     * @return a string containing the contents in an postorder traversal order
     */
    void postorder(TreeNode* thisNode, string& outString) const;

    /**
     * recursively delet nodes in a post order traversal
     * @param thisNode the current node
     */
    void postorderDelete(TreeNode* thisNode);

    /**
     * recursively count the number of nodes in the tree
     * @param thisNode our current node
     * @param numNodes current count
     */
    void count(TreeNode* thisNode, int& numNodes) const;

    /**
     * recursively insert Node contents into the array
     * @param root the starting place
     * @param the_array the array to insert into
     * @param next_index the next index to insert into
     */
    void inorderFillArray(TreeNode* thisNode, string the_array[], int& next_index);

};


#endif //BINARYSEARCHTREE_H
