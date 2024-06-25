#ifndef GRAPH_H
#define GRAPH_H

#include "bits/stdc++.h"
using namespace std;

class Graph {
public:
    struct Edge {
        int from;
        char label;
        int to;
    };
    
    Graph() = default;

    void addEdge(int from, char label, int to);
    static Graph loadFromFile(const string& filename);
    const unordered_map<int, vector<pair <char, int>>>& getEdges() const;
    
private:
    unordered_map<int, vector<pair<char, int>>> edges;
};
#endif // GRAPH_H