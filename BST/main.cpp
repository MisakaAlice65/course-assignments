#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main() {
    BinarySearchTree<int> bst;
    bst.insert(19);
    bst.insert(10);
    bst.insert(25);
    bst.insert(9);
    bst.insert(15);
    bst.insert(21);
    bst.insert(26);
    bst.insert(23);
    bst.printTree();
    printf("\n");
    bst.remove(19);
    bst.printTree();
    printf("\n");
    bst.remove(9);
    bst.printTree();
    printf("\n");
    bst.remove(10);
    bst.printTree();
    printf("\n");
    bst.remove(100);
    bst.printTree();
    printf("\n");
    BinarySearchTree<int> bst1;

    

}