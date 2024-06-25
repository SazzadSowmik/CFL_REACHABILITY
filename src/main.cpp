#include "bits/stdc++.h"
#include "graph.h"
#include "reachability.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file> ..." << endl;
        return 1;
    }

    // Loop through input files and process each one
    for (int i = 1; i < argc; ++i) {
        string input_file = argv[i];
        Graph graph = Graph::loadFromFile(input_file);

        // Print the edges of the graph
        const auto& edges = graph.getEdges();
        cout << "Edges in the graph from file: " << input_file << endl;
        for (const auto& node : edges) {
            int from = node.first;
            for (const auto& edge : node.second) {
                char label = edge.first;
                int to = edge.second;
                cout << from << " " << label << " " << to << endl;
            }
        }




        // auto result = reachabilityAnalysis(graph);
        
        // // Output the results
        // cout << "Results for file: " << input_file << endl;
        // for (const auto& pair : result) {
        //     cout << "(" << pair.first << ", " << pair.second << ")" << endl;
        // }
    }

    return 0;
}