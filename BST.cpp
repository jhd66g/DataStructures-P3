#include "BST.h"

// default constructor
BST::BST(): root{nullptr}, count{0}{}

// destructor
BST::~BST(){
    destroy(root);
}

// returns count
unsigned int BST::getCount(){
    return count;
}

// recursive helper function for destructor
void BST::destroy(Node* n){
    if (n != nullptr){
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
}

// inserts value in tree
void BST::insert(int val){
    Node* curr = root; // start at root
    Node* parent = nullptr; // to keep track of parent of curr node
    while (curr != nullptr){
        parent = curr;
        if (val < (curr->data)){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
        count ++;
    }
    Node* newNode = new Node(val); // create new node w data = val
    if (parent == nullptr){ // tree was empty, make newNode the root
        root = newNode;
    }
    else if (val < (parent->data)){ // attach newNode to left of parent
        parent->left = newNode;
        count ++;
    }
    else{ // attach newNode to right of parent
        parent->right = newNode;
        count ++;
    }
}


// searches for value
bool BST::search(int val){
    Node* curr = root; // start at root
    while (curr != nullptr){
        if ((curr->data) == val){
            return true;
        }
        else if (val < (curr->data)){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
        count ++;
    }
    return false; // val not found
}

// removes value
void BST::remove(int val){
    Node* curr = root; // start at root
    Node* parent = nullptr; // initialize parent to null
    while (curr != nullptr){
        count ++;
        if (val < (curr->data)){ // move left
            parent = curr; // update parent
            curr = curr->left;
        }
        else if (val > (curr->data)){  // move right
            parent = curr; // update parent
            curr = curr->right;
        }
        else{ // node found
            count ++; // traversal, have to go down one to find replacement
            // if curr has no children, delete
            if (curr->left == nullptr && curr->right == nullptr){
                if (parent == nullptr){ // curr is root
                    root = nullptr;
                } 
                else if (parent->left == curr){
                    parent->left = nullptr;
                } 
                else{
                    parent->right = nullptr;
                }
                delete curr;
            }
            // if curr has only left child, replace curr with left child
            else if (curr->left != nullptr && curr->right == nullptr){
                if (parent == nullptr){ // curr is root
                    root = curr->left;
                } 
                else if (parent->left == curr){
                    parent->left = curr->left;
                }
                else{
                    parent->right = curr->left;
                }
                delete curr;
            }
            // if curr has only right child, replace curr with right child
            else if (curr->left == nullptr && curr->right != nullptr){
                if (parent == nullptr){ // curr is root
                    root = curr->right;
                } 
                else if (parent->left == curr){
                    parent->left = curr->right;
                } 
                else{
                    parent->right = curr->right;
                }
                delete curr;
            }
            // if curr has two children, find successor (smallest in right subtree)
            else{
                Node* successor = curr->right;
                Node* successorParent = curr;
                while (successor->left != nullptr){
                    successorParent = successor;
                    successor = successor->left;
                    count ++;
                }
                curr->data = successor->data;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } 
                else{
                    successorParent->right = successor->right;
                }
                delete successor;
            }
            return;
        }
    }
}

// displays BST
void BST::display(){
    print(root);
    cout << endl;
}

// display helper function 
void BST::print(Node* curr){
    if (curr == nullptr){
        cout << "[]";
        return;
    }
    cout << "[" << curr->data;
    if (curr->left != nullptr || curr->right != nullptr){
        print(curr->left);
        print(curr->right);
    } 
    cout << "]";
}