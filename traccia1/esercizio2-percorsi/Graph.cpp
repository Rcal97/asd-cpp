#include "Graph.h"
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

//Costruttore
Graph::Graph(int N) : N(N), adj(N) {}

//AddEdge
//Grafo non orientato: aggiunge l'arco in entrambe le direzioni
void Graph::addEdge(int src, int dest, int cost){
    adj[src].push_back({dest,cost});
    adj[dest].push_back({src,cost});
}

//reconstructPath
//Risale il vettore parent da dest fino alla sorgente 0
//e ricostruisce il percorso come stringa "0->...->dest"
string Graph::reconstructPath(const vector<int>& parent, int dest) {
    vector<int> path;
    int v = dest;
    while (v != -1) {
        path.push_back(v);
        v = parent[v];
    }

    reverse(path.begin(), path.end());

    string result = "";
    for (int i = 0; i < (int)path.size(); i++) {
        if (i > 0) result += "->";
        result += to_string(path[i]);
    }
    return result;
}
//Dijkstra
void Graph::dijkstra(){
    vector<int> dist(N,INF);

    vector<int> totalCost(N, INF);
    vector<int> maxEdge(N,0);

    vector<int> parent(N,-1);

    //MinHeap
    priority_queue<State, vector<State>, greater<State>> pq;
    
    //Inizializzazione dalla capitale (nodo 0)
    dist[0] = 0;
    totalCost[0] = 0;
    maxEdge[0] = 0;
    pq.push({0,0,0});

    while(!pq.empty()){
        State curr = pq.top();
        pq.pop();

        //Stato obsoleto, già trovato un percorso migliore
        if(curr.effectiveCost() > dist[curr.node])
            continue;

        for(const Edge& e : adj[curr.node]){
            int newTotal = curr.totalCost + e.cost;
            int newMax = max(curr.maxCost, e.cost);
            int newEff = newTotal - newMax;

            if(newEff < dist[e.dest]) {
                dist[e.dest] = newEff;
                totalCost[e.dest] = newTotal;
                maxEdge[e.dest] = newMax;
                parent[e.dest] = curr.node;
                pq.push({newTotal, newMax, e.dest});
            }
        }
    }

    //Output
    for(int v=1; v<N; v++){
        if(dist[v] == INF){
            cout << "Città " << v << ": non raggiungibile" << endl;
        }
        else{
            string path = reconstructPath(parent,v);
            cout << path << " = " << totalCost[v] << "-" << maxEdge[v] << "=" << dist[v] << endl;
        }
    }
}