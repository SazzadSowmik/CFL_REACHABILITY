#include "reachability.h"

struct Production {
    char lhs;
    string rhs;
};

vector<pair<int, int>> reachabilityAnalysis(const Graph& graph) {
    vector<pair<int, int>> result;
    unordered_map<int, vector<pair<char, int>>> edges = graph.getEdges();
    queue<tuple<int, int, char>> W;
    unordered_map<int, unordered_map<int, unordered_set<char>>> reach;

    // CFG for balanced parentheses
    vector<Production> productions = {
        {'S', "SS"},
        {'S', "(S)"},
        {'S', "()"},
        {'S', ""}
    };

    // Init procedure
    for (const auto& [u, adj] : edges) {
        for (const auto& [a, v] : adj) {
            reach[u][v].insert(a);
            W.push({u, v, a});
        }
    }

    // Add epsilon transitions
    for (const auto& [u, _] : edges) {
        reach[u][u].insert('S');  // Empty string is always balanced
        W.push({u, u, 'S'});
    }

    // Solve procedure
    while (!W.empty()) {
        auto [u, v, Y] = W.front();
        W.pop();

        // Apply productions
        for (const auto& prod : productions) {
            if (prod.rhs.empty() && Y == 'S') {
                // S -> ε (already handled in init)
            } else if (prod.rhs == "()" && Y == ')') {
                // S -> ()
                for (const auto& [w, w_edges] : edges) {
                    for (const auto& [label, x] : w_edges) {
                        if (x == u && label == '(' && reach[w][v].insert('S').second) {
                            W.push({w, v, 'S'});
                        }
                    }
                }
            } else if (prod.rhs == "(S)" && Y == 'S') {
                // S -> (S)
                for (const auto& [w, w_edges] : edges) {
                    for (const auto& [label1, x] : w_edges) {
                        if (x == u && label1 == '(') {
                            for (const auto& [label2, y] : edges[v]) {
                                if (label2 == ')' && reach[w][y].insert('S').second) {
                                    W.push({w, y, 'S'});
                                }
                            }
                        }
                    }
                }
            } else if (prod.rhs == "SS" && Y == 'S') {
                // S -> SS
                for (const auto& [w, _] : edges) {
                    if (reach[u][w].count('S') && reach[w][v].count('S')) {
                        if (reach[u][v].insert('S').second) {
                            W.push({u, v, 'S'});
                        }
                    }
                }
            }
        }
    }

    // Collect results
    for (const auto& [u, adj] : reach) {
        for (const auto& [v, labels] : adj) {
            if (labels.count('S') && u != v) {
                result.emplace_back(u, v);
            }
        }
    }

    return result;
}