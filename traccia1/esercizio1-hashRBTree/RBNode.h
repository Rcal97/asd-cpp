#pragma once
#include <string>
#include <list>

using namespace std;

enum Color{RED, BLACK};

//Coppia chiave-valore memorizzata nella lista di collisione
struct KeyValue{
    string key;
    string value;
};

//Nodo del Red-Black Tree
class RBNode{
    public:
    int id; //hash della chiave
    Color color; //RED o BLACK
    list<KeyValue> items; //lista per gestire le collisioni
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int id, const string& key, const string& value) 
        : id(id), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
            items.push_back({key,value});
        }
};