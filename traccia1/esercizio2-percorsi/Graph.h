#pragma once

#include <vector>
#include <string>
#include <limits>

using namespace std;

//Rappresenta una tratta verso una città di destinazione con il suo costo
struct Edge{
    int dest;
    int cost;
};

/*
Stato nella coda di priorità di Dijkstra
Tiene traccia del costo totale, della tratta massima e del nodo corrente
*/
struct State{
    int totalCost; //somma dei costi delle tratte percorse
    int maxCost; //costo della tratta più onerosa del percorso
    int node; //nodo corrente

    //Il costo effettivo è totalCost - maxCost (dopo lo sconto)
    int effectiveCost() const{
        return totalCost - maxCost;
    }

    //Operatore per la coda di priorità (min-heap sul costo efettivo)
    bool operator>(const State& other) const{
        return effectiveCost() > other.effectiveCost();
    }
};

class Graph{
    private:
        int N; //numero di città
        vector<vector<Edge>> adj; //lista di adiacenza

        //Ricostruzione del percorso dalla città src alla città dest
        string reconstructPath(const vector<int>& parent, int dest);

    public:
        Graph(int N);

        //Aggiunge una tratta bidirezionale tra src e dest con costo cost
        void addEdge(int src, int dest, int cost);

        //Dijkstra modificato: calcola il percorso più economico
        //dalla capitale(nodo 0) a tutte le altre città
        void dijkstra();
};