#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "BST.h"
#include "SplayTree.h"

using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::istringstream;

int main(int argc, char* argv[]){
    // open file and create BST
    ifstream fstr(argv[1]); // opens file by command line
    string line;
    int lineNumber {0};

    // create BST
    BST tree1;

    // read file and operate
    auto start1 = std::chrono::steady_clock::now(); 
    while (getline(fstr, line)){ 
        lineNumber ++;
        // insert
        if (lineNumber == 1){
            istringstream iss(line);
            int n;
            while (iss >> n) {
                tree1.insert(n);
            }
            tree1.display();
        }
        // search
        else if (lineNumber == 3){
            istringstream iss(line);
            int n;
            while (iss >> n) {
                tree1.search(n);
            }
        }
        // remove
        else if (lineNumber == 5){
            istringstream iss(line);
            int n;
            while (iss >> n) {
                tree1.remove(n);
            }
        }
    }
    auto end1 = std::chrono::steady_clock::now(); // end time 
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds> (end1 - start1).count();
    tree1.display();
    cout << "BST traversal time: " << duration1 << " nanoseconds" << endl;
    cout << "BST traversal count: " << tree1.getCount() << endl;

    // reset file
    fstr.clear();
    fstr.seekg(0, std::ios::beg);
    lineNumber = 0;

    // create SplayTree
    SplayTree tree2;

    // read file and operate
    auto start2 = std::chrono::steady_clock::now(); 
    while (getline(fstr, line)){ 
        lineNumber ++;
        // insert
        if (lineNumber == 1){
            istringstream iss(line);
            int n;
            while (iss >> n) {
                tree2.insert(n);
            }
            tree2.display();
        }
        // search
        else if (lineNumber == 3){
            istringstream iss(line);
            int n;
            while (iss >> n) {
                tree2.search(n);
            }
        }
        // remove
        else if (lineNumber == 5){
            istringstream iss(line);
            int n;
            while (iss >> n) {
                tree2.remove(n);
            }
        }
    }
    auto end2 = std::chrono::steady_clock::now(); // end time 
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - start2).count();
    tree2.display();
    cout << "SplayTree traversal time: " << duration2 << " nanoseconds" << endl;
    cout << "SplayTree traversal count: " << tree2.getCount() << endl;

    // compare results 
    if (duration1 < duration2){
        cout << "BST was faster" << endl;
    }
    else{
        cout << "SplayTree was faster" << endl;
    }
    if (tree1.getCount() < tree2.getCount()){
        cout << "BST had less traversals" << endl;
    }
    else{
        cout << "SplayTree had less traversals" << endl;
    }

    
    fstr.close();
    return 0;
}