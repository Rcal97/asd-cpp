# Algoritmi e Strutture Dati — Traccia 1

**Corso**: Algoritmi e Strutture Dati  
**Docente**: Prof. Ferone  
**Anno Accademico**: 2021-2022  
**Studente**: Raffaele Calcagno  
**Linguaggio**: C++17  
**Build system**: CMake 3.10  

---

## Struttura del Repository
asd-cpp/

└── traccia1/

├── esercizio1-hashRBTree/

│   ├── RBNode.h

│   ├── HashRBTree.h

│   ├── HashRBTree.cpp

│   ├── main.cpp

│   ├── CMakeLists.txt

│   └── relazione/

└── esercizio2-percorsi/

├── Graph.h

├── Graph.cpp

├── main.cpp

├── input.txt

├── CMakeLists.txt

└── relazione/

---

## Esercizio 1 — HashRBTree

Struttura dati ibrida che combina un **Red-Black Tree** con una **funzione di hash**.
Le chiavi vengono trasformate in interi tramite l'algoritmo djb2 e usate come
identificatori dei nodi nell'albero. Le collisioni vengono gestite tramite una
lista concatenata associata a ciascun nodo.

**Operazioni supportate**: `INSERT`, `SEARCH`, `DELETE`, `PRINT`

**Complessità**: `O(m + log n)` per tutte le operazioni, dove `m` è la lunghezza
della chiave e `n` è il numero di nodi nell'albero.

### Compilazione ed Esecuzione

```bash
cd traccia1/esercizio1-hashRBTree
mkdir -p build && cd build
cmake ..
make
./hashRBTree
```

---

## Esercizio 2 — Percorsi nell'Arcipelago

Variante dell'algoritmo di **Dijkstra** per trovare il percorso più economico
dalla capitale (nodo 0) a tutte le altre città di un grafo pesato non orientato.
Lo sconto applicato è pari al costo della tratta più onerosa dell'intero percorso.

La funzione obiettivo da minimizzare è:

$$f(\pi) = \sum_{e \in \pi} c(e) - \max_{e \in \pi} c(e)$$

**Complessità**: `O(P log P)` dove `P` è il numero di tratte.

### Compilazione ed Esecuzione

```bash
cd traccia1/esercizio2-percorsi
mkdir -p build && cd build
cmake ..
make
./percorsi ../input.txt
```

### Formato Input
N P

S1 E1 C1

S2 E2 C2

dove `N` = numero città, `P` = numero tratte, `S E C` = partenza, arrivo, costo.

### Esempio
Input:          Output:

4 6             0->1 = 4-4=0

0 1 4           0->2 = 1-1=0

0 2 1           0->2->3 = 5-4=1

1 3 2           0->1->4 = 16-12=4

1 4 12

2 3 4

3 4 5

---

## Requisiti

- GCC 13+ con supporto C++17
- CMake 3.10+