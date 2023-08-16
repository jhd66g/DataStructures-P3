#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using std::ifstream;
using std::cout;
using std::endl;

#ifndef SplayTree_H
#define SplayTree_H

struct sNode{
    int data;
    sNode* left;
    sNode* right;
    sNode* parent;
    sNode(int val): data(val), left(nullptr), right(nullptr), parent(nullptr){}
};

class SplayTree{
    private:
        sNode* root;
        unsigned int count;

    public: 
        // default constructor
        SplayTree();

        // destructor
        ~SplayTree();

        // returns count
        unsigned int getCount();

        // recursive helper function for destructor
        void destroy(sNode* );

        // splays node to the root
        void splay(sNode* );

        // rotates node left
        void rotateLeft(sNode* );

        // rotates node right
        void rotateRight(sNode* );

        // inserts value in tree
        void insert(int );

        // searches for value
        bool search(int );

        // removes value
        void remove(int );

        // displays BST
        void display();

        // display helper function
        void print(sNode* );
};

#endif