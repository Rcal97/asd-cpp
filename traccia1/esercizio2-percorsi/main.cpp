#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: ./percorsi <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Errore: impossibile aprire il file " << argv[1] << endl;
        return 1;
    }

    int N, P;
    file >> N >> P;

    // Le città sono numerate da 0 a N-1
    // ma la traccia dice "numerate da 1 a N, 0 è la capitale"
    // quindi il grafo ha N+1 nodi
    Graph g(N + 1);

    for (int i = 0; i < P; i++) {
        int S, E, C;
        file >> S >> E >> C;
        g.addEdge(S, E, C);
    }

    file.close();

    g.dijkstra();

    return 0;
}