#include "bits/stdc++.h"
#include "graph.h"
#include "reachability.h"

using namespace std;


int main() {
    string graphFilename = "../data/example_input.txt";

    // Load graph
    Graph graph;
    try {
        graph = Graph::loadFromFile(graphFilename);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }


    // Print loaded graph and CFG for verification
    // cout << "Graph loaded successfully:\n";
    // const auto& edges = graph.getEdges();
    // for (const auto& [from, edgeList] : edges) {
    //     for (const auto& [label, to] : edgeList) {
    //         cout << from << " " << label << " " << to << endl;
    //     }
    // }


    // Perform reachability analysis
    auto result = reachabilityAnalysis(graph);
    
    // Output the results
    cout << "All Reachable Pairs for file: " << graphFilename << endl;
    for (const auto& pair : result) {
        cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    }

    return 0;
}