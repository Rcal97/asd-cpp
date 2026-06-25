#include <iostream>
#include "HashRBTree.h"

using namespace std;

int main(){
    HashRBTree tree;

    cout << " INSERT " << endl;
    tree.insert("apple", "frutto rosso");
    tree.insert("banana", "frutto giallo");
    tree.insert("cherry", "frutto rosso piccolo");
    tree.insert("date", "frutto dolce");
    tree.insert("elderberry", "frutto viola");
    tree.insert("fig", "frutto mediterraneo");
    tree.insert("grape", "frutto a grappolo");

    cout << "\n PRINT (dopo inserimenti) " << endl;
    tree.print();

    cout << "\n SEARCH " << endl;
    tree.search("apple", "");
    tree.search("banana", "");
    tree.search("mango", ""); // chiave non presente

    cout << "\n COLLISIONE " << endl;
    //Inseriamo due chiavi che potrebbero collidere (dipende dalla funzione di hash)
    tree.insert("listen", "ascoltare");
    tree.insert("silent", "silenzioso");   //anagramma, hash diverso ma test utile
    tree.print();

    cout << "\n REMOVE " << endl;
    tree.remove("banana", "");
    tree.remove("mango", ""); //non esiste
    cout << "\nAlbero dopo rimozione: " << endl;
    tree.print();

    tree.remove("apple", "");
    tree.remove("cherry", "");
    cout << "\n Albero dopo rimozione due elementi" << endl;
    tree.print();

    return 0;
}