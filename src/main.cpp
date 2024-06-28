#include "bits/stdc++.h"
#include "graph.h"
#include "reachability.h"
#include "cfg.h"

using namespace std;


int main() {
    string graphFilename = "../data/example_input.txt";
    string cfgFilename = "../data/cfg_input.txt";

    // Load graph
    Graph graph;
    try {
        graph = Graph::loadFromFile(graphFilename);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // Load CFG
    CFG cfg;
    try {
        cfg = CFG::loadFromFile(cfgFilename);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // Print loaded graph and CFG for verification
    cout << "Graph loaded successfully:\n";
    const auto& edges = graph.getEdges();
    for (const auto& [from, edgeList] : edges) {
        for (const auto& [label, to] : edgeList) {
            cout << from << " " << label << " " << to << endl;
        }
    }

    cout << "\nCFG loaded successfully:\n";
    cout << "Start Symbol: " << cfg.getStartSymbol() << endl;
    const auto& productions = cfg.getProductions();
    for (const auto& production : productions) {
        for (const auto& rule : production.rules) {
            cout << production.nonTerminal << " -> " << rule << endl;
        }
    }
    cout << endl;

    // Perform reachability analysis
    auto result = reachabilityAnalysis(graph, productions, cfg.getStartSymbol());
    
    // Output the results
    cout << "Results for file: " << graphFilename << endl;
    for (const auto& pair : result) {
        cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    }

    return 0;
}