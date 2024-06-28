#ifndef REACHABILITY_H
#define REACHABILITY_H

#include "bits/stdc++.h"
#include "graph.h"
#include "cfg.h"

using namespace std;

vector<pair<int, int>> reachabilityAnalysis(const Graph& graph, const vector<CFG::Production>& productions, char startSymbol);

#endif // REACHABILITY_H