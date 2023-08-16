#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using std::ifstream;
using std::cout;
using std::endl;

#ifndef BST_H
#define BST_H

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val): data(val), left(nullptr), right(nullptr){}
};

class BST{
    private:
        Node* root;
        unsigned int count;

    public: 
        // default constructor
        BST();

        // destructor
        ~BST();

        // returns count
        unsigned int getCount();

        // recursive helper function for destructor
        void destroy(Node* );

        // inserts value in tree
        void insert(int );

        // searches for value
        bool search(int );

        // removes value
        void remove(int );

        // displays BST
        void display();

        // display helper function
        void print(Node* );
};

#endif