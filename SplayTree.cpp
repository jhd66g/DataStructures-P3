#include "SplayTree.h"

// default constructor
SplayTree::SplayTree(): root{nullptr}, count{0}{}

// destructor
SplayTree::~SplayTree(){
    destroy(root);
}

// returns count
unsigned int SplayTree::getCount(){
    return count;
}

// recursive helper function for destructor
void SplayTree::destroy(sNode* n){
    if (n != nullptr){
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
}

// splays node to the root
void SplayTree::splay(sNode* n){
    sNode* parent = nullptr;
    sNode* grandparent = nullptr;
    while (n->parent != nullptr){
        parent = n->parent;
        grandparent = parent->parent;
        if (grandparent == nullptr){
            // n is left child
            if (n == parent->left) {
                rotateRight(parent);
            } 
            // n is right child
            else {
                rotateLeft(parent);
            }
        } 
        else if ((parent == grandparent->left && n == parent->left) 
            || (parent == grandparent->right && n == parent->right)){
            // n is left child of left child
            if (n == parent->left){
                rotateRight(grandparent);
                rotateRight(parent);
            } 
            // n is right child of right child
            else{
                rotateLeft(grandparent);
                rotateLeft(parent);
            }
        } 
        else{
            // n is left child of right child
            if (n == parent->left){
                rotateRight(parent);
                rotateLeft(grandparent);
            } 
            // n is right child of left child
            else{
                rotateLeft(parent);
                rotateRight(grandparent);
            }
        }
        count ++;
    }
}


// rotates node left
void SplayTree::rotateLeft(sNode* n){
    sNode* r = nullptr;
    if (n->right != nullptr){
        r = n->right;
        n->right = r->left;
        if (r->left != nullptr){
            r->left->parent = n;
        }
        r->parent = n->parent;
        if (n->parent == nullptr){ 
            root = r;
        } 
        else if (n == n->parent->left){ 
            n->parent->left = r; 
        }
        else{ 
            n->parent->right = r; 
        } 
        r->left = n; 
        n->parent = r; 
    }
    return;
}

// rotates node right
void SplayTree::rotateRight(sNode* n){
    sNode* l = nullptr; 
    if (n->left != nullptr) {
        l = n->left;
        n->left = l->right; 
        if (l->right != nullptr){ 
            l->right->parent = n; 
        } 
        l->parent = n->parent; 
        if (n->parent == nullptr){ 
            root = l;
        } 
        else if (n == n->parent->left){ 
            n->parent->left = l; 
        } 
        else{ 
            n->parent->right = l; 
        } 
        l->right = n; 
        n->parent = l; 
    } 
    return;
}

// inserts value in tree
void SplayTree::insert(int val){
    sNode* curr = root; // start at root
    while (curr != nullptr){
        if (val < (curr->data)){
            if (curr->left == nullptr){
                break;
            }
            curr = curr->left;
        }   
        else{
            if (curr->right == nullptr){
                break;
            }
            curr = curr->right;
        }
        count ++;
    }
    sNode* newNode = new sNode(val); // create new sNode w data = val
    if (root == nullptr){ // tree was empty, make newNode the root
        root = newNode;
    }
    else if (val < (curr->data)){ // attach newNode to left of parent
        curr->left = newNode;
        newNode->parent = curr;
        count ++;
    }
    else{ // attach newNode to right of parent
        curr->right = newNode;
        newNode->parent = curr;
        count ++;
    }
    splay(newNode);
    return;
}


// searches for value
bool SplayTree::search(int val){
    sNode* curr = root; // start at root
    sNode* parent = nullptr;
    while (curr != nullptr){
        parent = curr;
        if ((curr->data) == val){
            splay(curr);
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
    splay(parent);
    return false; // val not found
}

// removes value
void SplayTree::remove(int val){
    // if val exist, splays item to remove to root
    if (search(val)){
        sNode* toDelete = nullptr;
        // if root has no left child
        if (root->left == nullptr){
            toDelete = root;
            root = root->right;
            root->parent = nullptr;
        }
        // if root has no right child
        else if (root->right == nullptr){
            toDelete = root;
            root = root->left;
            root->parent = nullptr;
        }
        // find largest in left subtree and splay
        else{
            sNode* successor = root->left;
            while (successor->right != nullptr){
                successor = successor -> right;
            }
            splay(successor);
            // delete right child of new root 
            toDelete = root->right;
            sNode* rightChild = toDelete->right;
            root->right = rightChild;
            rightChild->parent = root;
        }
        delete toDelete;
    }
    
    return;
}

// displays BST
void SplayTree::display(){
    print(root);
    cout << endl;
}

// display helper function 
void SplayTree::print(sNode* curr){
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