#include "cfg.h"

void CFG::addProduction(char nonTerminal, const string& rule) {
    for (auto& production : productions) {
        if (production.nonTerminal == nonTerminal) {
            production.rules.push_back(rule);
            return;
        }
    }
    productions.push_back({nonTerminal, {rule}});
}

CFG CFG::loadFromFile(const string& filename) {
    CFG cfg;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    bool isFirstLine = true;
    while (getline(file, line)) {
        if (isFirstLine) {
            cfg.startSymbol = line[0];
            isFirstLine = false;
        } else {
            size_t arrowPos = line.find("->");
            if (arrowPos == string::npos) {
                throw runtime_error("Invalid line format: " + line);
            }
            char nonTerminal = line[0];
            string rule = line.substr(arrowPos + 2); // Skip past "->"
            // Remove any leading or trailing whitespace from rule
            rule.erase(0, rule.find_first_not_of(' ')); // Leading
            rule.erase(rule.find_last_not_of(' ') + 1); // Trailing
            cfg.addProduction(nonTerminal, rule);
        }
    }

    return cfg;
}

const vector<CFG::Production>& CFG::getProductions() const {
    return productions;
}

char CFG::getStartSymbol() const {
    return startSymbol;
}