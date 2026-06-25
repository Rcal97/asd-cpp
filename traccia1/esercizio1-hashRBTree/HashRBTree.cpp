#include "HashRBTree.h"

//Hash Function
//hash = hash * 33 + c, per ogni carattere c della chiave
//Restituisce un intero non negativo(maschera con 0x7FFFFFFF)
int HashRBTree::hashFunction(const string& key){
    unsigned long hash = 5381;
    for(char c : key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash & 0x7FFFFFFF; // Restituisce un intero non negativo
}

//Costruttore
//NIL è il nodo sentinella condiviso: BLACK, id=0, punta a se stesso
//Tutti i "nullptr" dell'RBTree classico diventano puntatori a NIL.
HashRBTree::HashRBTree(){
    NIL = new RBNode(0, "", "");
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    root = NIL;
}

//Distruttore
HashRBTree::~HashRBTree(){
    destroyTree(root);
    delete NIL;
}

//Visita post-order per deallocare tutti i nodi (escluso NIL)
void HashRBTree::destroyTree(RBNode* node){
    if(node == NIL)
        return;
    else{   
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

//Left Rotate
void HashRBTree::leftRotate(RBNode* x){
    RBNode* y = x->right; // y è il figlio sinistro di x
    x->right = y->left; //Il sottoalbero sinistro di y diventa figlio destro di x

    if(y->left != NIL)
        y->left->parent = x; 
    
        y->parent = x->parent; //y prende il parent di x

    if(x->parent == NIL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

//Right Rotate
void HashRBTree::rightRotate(RBNode* y){
    RBNode* x = y->left; // x è il figlio sinistro di y
    y->left = x->right; //Il sottoalbero destro di x diventa figlio sinistro di y

    if(x->right != NIL)
        x->right->parent = y; 
    
        x->parent = y->parent; //x prende il parent di y

    if(y->parent == NIL)
        root = x;
    else if(y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

/*
INSERT
Se la chiave ha lo stesso hash di un nodo già presente, si ha una collisione
aggiunge la coppia key,value alla lista del nodo esistente.
Altrimenti crea un nuovo nodo e lo inserisce come in un BST classico,
poi chiama insertFix per ripristinare le proprieta del RBTree
*/
void HashRBTree::insert(const string& key, const string& value){
    int id = hashFunction(key);

    //Cerca se esiste già un nodo con questo id
    RBNode* existing = searchNode(id);
    if(existing != NIL){
        existing->items.push_back({key,value});
        return;
    }

    //Nodo nuovo
    RBNode* z = new RBNode(id, key, value);
    z->left = NIL;
    z->right = NIL;
    z->parent = NIL;

    //BST insert
    RBNode* y = NIL;
    RBNode* x = root;

    while(x != NIL){
        y = x;
        if(z->id < x->id)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if(y == NIL)
        root = z;
    else if(z->id < y->id)
        y->left = z;
    else
        y->right = z;

    insertFix(z);
}

/*
INSERT FIX
Ripristina le proprietà RBT dopo un inserimento.
Un nodo inserito è sempre RED: l'unica proprietà che può violare
è l'ottenere due nodi rossi consecutivi (proprietà 4 .
*/
void HashRBTree::insertFix(RBNode* z){
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            RBNode* y = z->parent->parent->right; //lo zio
            if(y->color == RED){ //Caso 1: lo zio è rosso
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else { //Caso 2 e 3: lo zio è nero
                if(z == z->parent->right){ //Caso 2: z è figlio destro
                    z = z->parent;
                    leftRotate(z);
                }
                //Caso 3: z è figlio sinistro
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else { //Speculare al caso precedente
            RBNode* y = z->parent->parent->left; //lo zio
            if(y->color == RED){ //Caso 1: lo zio è rosso
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else { //Caso 2 e 3: lo zio è nero
                if(z == z->parent->left){ //Caso 2: z è figlio sinistro
                    z = z->parent;
                    rightRotate(z);
                }
                //Caso 3: z è figlio destro
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK; //La radice deve essere sempre nera
}

/*
SEARCH NODE
Ricerca interna: naviga l RBT tramite l'id(hash della chiave)
Restituisce il nodo con quell'id, oppure NIL se non esiste
*/

RBNode* HashRBTree::searchNode(int id){
    RBNode* x = root;

    while(x != NIL){
        if(id == x->id)
            return x;
        else if(id < x->id)
            x = x->left;
        else
            x = x->right;
    }

    return NIL; //Nodo non trovato
}

/*
SEARCH
Ricerca pubblica: data una chiave, calcola il valore hash
trova il nodo, poi scorre la lista di collisione cercando la chiave.
Stampa il valore se trovato, altrimenti un messaggio di errore.
*/
void HashRBTree::search(const string& key, const string& value){
    int id = hashFunction(key);
    RBNode* node = searchNode(id);

    if(node == NIL){
        cout << "Chiave " << key << " non trovata " << endl;
        return;
    }

    //Scorre la lista per trovare la chiave
    for(const KeyValue& kv : node->items){
        if(kv.key == key){
            cout << "Trovato: "  << kv.key << " -> " << kv.value << endl;
            return;
        }
    }

    cout << "Chiave " << key << " non trovata nella lista di collisione" << endl;
}

// ─── Minimum ──────────────────────────────────────────────────────────────────
// Restituisce il nodo con id minimo nel sottoalbero radicato in x.
// Scende sempre a sinistra fino a NIL.
RBNode* HashRBTree::minimum(RBNode* x) {
    while (x->left != NIL)
        x = x->left;
    return x;
}

// ─── Transplant ───────────────────────────────────────────────────────────────
// Sostituisce il sottoalbero radicato in u con quello radicato in v.
// Non aggiorna v->left e v->right: lo fa remove() dopo.
void HashRBTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == NIL)
        root = v;                   // u era la root
    else if (u == u->parent->left)
        u->parent->left = v;        // u era figlio sinistro
    else
        u->parent->right = v;       // u era figlio destro

    v->parent = u->parent;          // aggiorna il parent di v (anche se v == NIL)
}

// ─── Remove ───────────────────────────────────────────────────────────────────
// Rimozione in due fasi:
// 1) Se il nodo ha più entry nella lista (collisione), rimuove solo quella coppia.
// 2) Se la lista resta vuota, rimuove il nodo dall'albero e chiama deleteFix.
void HashRBTree::remove(const string& key, const string& value) {
    int id = hashFunction(key);
    RBNode* z = searchNode(id);

    if (z == NIL) {
        cout << "Chiave \"" << key << "\" non trovata." << endl;
        return;
    }

    // Cerca la coppia esatta nella lista
    for (auto it = z->items.begin(); it != z->items.end(); ++it) {
        if (it->key == key) {
            z->items.erase(it);
            break;
        }
    }

    // Se la lista non è vuota, il nodo rimane nell'albero
    if (!z->items.empty())
        return;

    // Lista vuota: rimuovi il nodo dall'albero
    RBNode* y = z;                  // y = nodo da rimuovere (o suo successore)
    RBNode* x = NIL;                // x = nodo che prende il posto di y
    Color yOriginalColor = y->color;

    if (z->left == NIL) {
        // Caso 1: z non ha figlio sinistro
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        // Caso 2: z non ha figlio destro
        x = z->left;
        transplant(z, z->left);
    } else {
        // Caso 3: z ha entrambi i figli → successore = minimo del sottoalbero destro
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;          // x potrebbe essere NIL, aggiorna comunque
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;        // y eredita il colore di z
    }

    delete z;

    // Se il nodo rimosso (o il successore) era BLACK, potremmo aver violato le proprietà
    if (yOriginalColor == BLACK)
        deleteFix(x);
}

// ─── DeleteFix ────────────────────────────────────────────────────────────────
// Ripristina le proprietà RBT dopo una rimozione.
// Viene chiamato solo se il nodo rimosso era BLACK (un nodo RED non cambia
// i conteggi di BLACK nei percorsi).
void HashRBTree::deleteFix(RBNode* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right; // fratello di x

            if (w->color == RED) {
                // ── Caso 1: fratello RED → leftRotate sul padre ────────────
                w->color          = BLACK;
                x->parent->color  = RED;
                leftRotate(x->parent);
                w = x->parent->right;   // nuovo fratello dopo rotazione
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                // ── Caso 2: fratello BLACK con figli BLACK → recoloring ────
                w->color = RED;
                x = x->parent;          // sali
            } else {
                if (w->right->color == BLACK) {
                    // ── Caso 3: fratello BLACK, figlio destro BLACK ────────
                    w->left->color = BLACK;
                    w->color       = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // ── Caso 4: fratello BLACK, figlio destro RED ─────────────
                w->color         = x->parent->color;
                x->parent->color = BLACK;
                w->right->color  = BLACK;
                leftRotate(x->parent);
                x = root;               // terminazione
            }
        } else {
            // Simmetrico: x è figlio DESTRO
            RBNode* w = x->parent->left;

            if (w->color == RED) {
                // ── Caso 1 simmetrico ─────────────────────────────────────
                w->color         = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                // ── Caso 2 simmetrico ─────────────────────────────────────
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // ── Caso 3 simmetrico ─────────────────────────────────
                    w->right->color = BLACK;
                    w->color        = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // ── Caso 4 simmetrico ─────────────────────────────────────
                w->color         = x->parent->color;
                x->parent->color = BLACK;
                w->left->color   = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK; // x RED o root: coloralo BLACK
}

/*
PRINT
Interfaccia pubblica: stampa l'albero visivamente.
Se l'albero è vuoto, stampa un messaggio, altrimenti chiama printHelper.
*/
void HashRBTree::print(){
    if(root == NIL){
        cout << "Albero vuoto." << endl;
        return;
    }
    printHelper(root, "", true);
}

/*
PRINT HELPER
Stampa l'albero in forma grafica con indentazione.
Formato per ogni nodo: [id] (RED/BLACK) -> lista di coppie key,value
indent: stringa di indentazione accumulata scendendo nell'albero
last: true se il nodo è l'ultimo figlio 
*/
void HashRBTree::printHelper(RBNode* node, string indent, bool last){
    if(node == NIL)
        return;

    cout << indent;

    if(last){
        cout << "└── ";
        indent += "    "; //i figli del nodo ultimo non hanno barra verticale
    }
    else{
        cout << "├── ";
        indent += "│   "; //i figli del nodo non ultimo hanno barra verticale
    }

    //Stampa id e colore
    string colorStr = (node->color == RED) ? "RED" : "BLACK";
    cout << "[" << node->id << "] (" << colorStr << ") -> ";

    //Stampa tutte le coppie nella lista (collisioni)
    bool first = true;
    for(const KeyValue& kv : node->items){
        if(!first) cout << ", ";
        cout << kv.key << ":" << kv.value;
        first = false;
    }
    cout << endl;

    //Ricorsione sui figli: il figlio destro è sempre stampato per ultimo per avere una visualizzazione più chiara
    printHelper(node->left, indent, false);
    printHelper(node->right, indent, true);
}