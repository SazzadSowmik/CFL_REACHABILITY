#include "graph.h"

void Graph::addEdge(int from, char label, int to) {
    edges[from].push_back({label, to});
}

Graph Graph::loadFromFile(const string& filename) {
    Graph graph;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int from, to;
        char label;
        if (!(iss >> from >> label >> to)) {
            throw runtime_error("Invalid line format: " + line);
        }
        graph.addEdge(from, label, to);
    }

    return graph;
}

const unordered_map<int, vector<pair<char, int>>>& Graph::getEdges() const {
    return edges;
}