#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
set<string> terminals;
set<string> nonTerminals;

bool isTerminal(string s) { return terminals.count(s); }

void computeFollow() {
    bool changed = true;

    string startSymbol = "E";
    FOLLOW[startSymbol].insert("$");

    while (changed) {
        changed = false;

        for (auto &prodPair : productions) {
            string lhs = prodPair.first;

            for (string rhs : prodPair.second) {
                int len = rhs.size();

                for (int i = 0; i < len; i++) {
                    string B(1, rhs[i]);

                    if (nonTerminals.count(B)) { 
                        set<string> followB = FOLLOW[B];
                        bool epsInNext = false;

                        for (int j = i + 1; j < len; j++) {
                            string next(1, rhs[j]);
                            set<string> firstNext = FIRST[next];

                            for (string s : firstNext)
                                if (s != "eps") FOLLOW[B].insert(s);

                            if (firstNext.find("eps") != firstNext.end())
                                epsInNext = true;
                            else {
                                epsInNext = false;
                                break;
                            }
                        }

                        if (i == len - 1 || epsInNext) {
                            for (string s : FOLLOW[lhs]) FOLLOW[B].insert(s);
                        }

                        if (FOLLOW[B].size() != followB.size())
                            changed = true;
                    }
                }
            }
        }
    }
}

int main() {
    productions["E"]  = {"TE'"};
    productions["E'"] = {"+TE'", "eps"};
    productions["T"]  = {"FT'"};
    productions["T'"] = {"*FT'", "eps"};
    productions["F"]  = {"(E)", "id"};

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
        for (auto s : FOLLOW[nt]) cout << s << " ";
        cout << "}\n";
    }

    return 0;
}
