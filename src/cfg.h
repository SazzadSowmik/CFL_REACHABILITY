#ifndef CFG_H
#define CFG_H

#include "bits/stdc++.h"
using namespace std;

class CFG {
public:
    struct Production {
        char nonTerminal;
        vector<string> rules;
    };

    CFG() = default;

    void addProduction(char nonTerminal, const string& rule);
    static CFG loadFromFile(const string& filename);
    const vector<Production>& getProductions() const;
    char getStartSymbol() const;

private:
    vector<Production> productions;
    char startSymbol;
};

#endif // CFG_H