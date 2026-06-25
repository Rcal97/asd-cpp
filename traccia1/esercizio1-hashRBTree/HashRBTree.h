#pragma once

#include <RBNode.h>
#include <iostream>

using namespace std;

class HashRBTree{
    private:
    RBNode* root;
    RBNode* NIL; //nodo sentinalla

    //Funzione di hash
    int hashFunction(const string& key);

    //Rotazioni per bilanciamento RBTree
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);

    //Fix dopo inserimento e cancellazione
    void insertFix(RBNode* z);
    void deleteFix(RBNode* x);

    //Transplant: sostituisce sottoalbero radicato in u con quello in v
    void transplant(RBNode* u, RBNode* v);

    //Minimo del sottoalbero
    RBNode* minimum(RBNode* x);

    //Ricerca nodo per id
    RBNode* searchNode(int id);

public:
    HashRBTree();
    ~HashRBTree();

    void insert(const string& key, const string& value);
    void search(const string& key, const string& value);
    void remove(const string& key, const string& value);
    void print();

private:
    void printHelper(RBNode* node, string indent, bool last);
    void destroyTree(RBNode* node);
};