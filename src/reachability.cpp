#include "reachability.h"

vector<pair<int, int>> reachabilityAnalysis(const Graph& graph) {
    vector<tuple<char, char, char>> productions = {
        {'S', '(', 'S'}, {'S', 'S', ')'}, {'S', 'ε', 'ε'}
    };

    unordered_map<int, unordered_set<int>> worklist;
    unordered_map<int, vector<pair<char, int>>> edges = graph.getEdges();

    queue<tuple<int, int, char>> W;

    // Initialize worklist with direct edges and epsilon transitions
    for (const auto& node : edges) {
        int u = node.first;
        for (const auto& adj : node.second) {
            int v = adj.second;
            char label = adj.first;
            if (label == 'ε') {
                W.push({u, v, label});
            } else {
                worklist[u].insert(v);
            }
        }
    }

    while (!W.empty()) {
        auto [u, v, A] = W.front();
        W.pop();

        for (const auto& [C, B, D] : productions) {
            if (A == B) {
                for (const auto& edge : edges[v]) {
                    if (edge.first == D && worklist[u].find(edge.second) == worklist[u].end()) {
                        worklist[u].insert(edge.second);
                        W.push({u, edge.second, C});
                    }
                }
            }
        }

        for (const auto& [C, D, B] : productions) {
            if (A == B) {
                for (const auto& node : edges) {
                    int w = node.first;
                    for (const auto& edge : node.second) {
                        if (edge.first == D && edge.second == u && worklist[w].find(v) == worklist[w].end()) {
                            worklist[w].insert(v);
                            W.push({w, v, C});
                        }
                    }
                }
            }
        }
    }

    vector<pair<int, int>> result;
    for (const auto& node : worklist) {
        int u = node.first;
        for (int v : node.second) {
            result.emplace_back(u, v);
        }
    }
    return result;
}