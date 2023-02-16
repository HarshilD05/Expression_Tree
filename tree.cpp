#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<vector>

struct TreeNode {
    std::string data;
    TreeNode *left;
    TreeNode *right;

    TreeNode (std::string s) : data(s),left(nullptr),right(nullptr) {}
};

class BinTree {
    void inOrder (TreeNode *root) {
        if (root == nullptr) return;
        inOrder(root->left);
        std::cout<< root->data <<" ";
        inOrder(root->right);
    }

    void preOrder (TreeNode *root) {
        if (root == nullptr) return;
        std::cout<< root->data <<" ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void postOrder (TreeNode *root) {
        if (root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        std::cout<< root->data <<" ";
    }

    public : 
    TreeNode *ROOT;

    BinTree (std::vector<int> nums);
    BinTree (TreeNode *r) : ROOT(r) {}

    void in_order() {
        inOrder(ROOT);
    }

    void pre_order() {
        preOrder(ROOT);
    }

    void post_order() {
        postOrder(ROOT);
    }

};


/*  Testing */
/*
int main () {
    TreeNode *x = new TreeNode("*");
    std::cout<< x->data ;

    return 0;
}
// */

#endif