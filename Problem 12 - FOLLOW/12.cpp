#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
set<string> terminals;
set<string> nonTerminals;

bool isTerminal(string s) {
    return terminals.count(s);
}

vector<string> splitSymbols(string prod) {
    vector<string> symbols;
    string temp;
    for (char ch : prod) {
        if (ch == ' ') {
            if (!temp.empty()) {
                symbols.push_back(temp);
                temp.clear();
            }
        } else {
            temp += ch;
        }
    }
    if (!temp.empty()) 
        symbols.push_back(temp);
    return symbols;
}

void computeFollow() {
    string startSymbol = "E";
    FOLLOW[startSymbol].insert("$");
    bool changed = true;

    while (changed) {
        changed = false;
        for (auto& pair : productions) {
            string lhs = pair.first;

            for (string rhs : pair.second) {
                vector<string> symbols = splitSymbols(rhs);
                
                int n = symbols.size();
                for (int i = 0; i < n; ++i) {
                    string B = symbols[i];
                    if (!nonTerminals.count(B)) 
                        continue;
                        
                    set<string> before = FOLLOW[B];

                    bool allEps = true;
                    for (int j = i + 1; j < n; ++j) {
                        for (string s : FIRST[symbols[j]])
                            if (s != "eps") 
                                FOLLOW[B].insert(s);
                        if (FIRST[symbols[j]].count("eps") == 0) {
                            allEps = false;
                            break;
                        }
                    }
                    if (i == n - 1 || allEps) {
                        for (string s : FOLLOW[lhs])
                            FOLLOW[B].insert(s);
                    }
                    if (FOLLOW[B].size() != before.size())
                        changed = true;
                }
            }
        }
    }
}

int main() {
    productions["E"]  = {"T E'"};
    productions["E'"] = {"+ T E'", "eps"};
    productions["T"]  = {"F T'"};
    productions["T'"] = {"* F T'", "eps"};
    productions["F"]  = {"( E )", "id"};

    nonTerminals = {"E", "E'", "T", "T'", "F"};
    terminals = {"+", "*", "(", ")", "id"};

    FIRST["E"]  = {"(", "id"};
    FIRST["E'"] = {"+", "eps"};
    FIRST["T"]  = {"(", "id"};
    FIRST["T'"] = {"*", "eps"};
    FIRST["F"]  = {"(", "id"};

    computeFollow();

    for (string nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (string s : FOLLOW[nt]) 
            cout << s << " ";
        cout << "}" << endl;
    }
}
