#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
vector<string> nonTerminals = {"E", "E'", "T", "T'", "F"};
vector<string> terminals = {"id", "+", "*", "(", ")", "$"};

map<string, map<string, string>> parseTable;

set<string> getFirstOfString(const string &alpha) {
    set<string> result;
    if (alpha == "eps") {
        result.insert("eps");
        return result;
    }

    for (int i = 0; i < alpha.size(); i++) {
        string sym(1, alpha[i]);
        if (FIRST.count(sym)) {
            set<string> f = FIRST[sym];
            for (auto s : f)
                if (s != "eps") result.insert(s);
            if (f.find("eps") == f.end()) break;
        } else {
            result.insert(sym);
            break;
        }
    }
    return result;
}

int main() {
    productions["E"]  = {"TE'"};
    productions["E'"] = {"+TE'", "eps"};
    productions["T"]  = {"FT'"};
    productions["T'"] = {"*FT'", "eps"};
    productions["F"]  = {"(E)", "id"};

    FIRST["E"]  = {"(", "id"};
    FIRST["E'"] = {"+", "eps"};
    FIRST["T"]  = {"(", "id"};
    FIRST["T'"] = {"*", "eps"};
    FIRST["F"]  = {"(", "id"};

    FOLLOW["E"]  = {")", "$"};
    FOLLOW["E'"] = {")", "$"};
    FOLLOW["T"]  = {"+", ")", "$"};
    FOLLOW["T'"] = {"+", ")", "$"};
    FOLLOW["F"]  = {"*", "+", ")", "$"};

    for (auto nt : nonTerminals) {
        for (auto prod : productions[nt]) {
            set<string> firstSet = getFirstOfString(prod);

            for (auto t : firstSet) {
                if (t != "eps")
                    parseTable[nt][t] = prod;
            }

            if (firstSet.find("eps") != firstSet.end()) {
                for (auto f : FOLLOW[nt]) {
                    parseTable[nt][f] = prod;
                }
            }
        }
    }

    cout << "\nLL(1) Parsing Table:\n\n";
    cout << "\t";
    for (auto t : terminals) cout << t << "\t";
    cout << "\n";

    for (auto nt : nonTerminals) {
        cout << nt << "\t";
        for (auto t : terminals) {
            if (parseTable[nt].count(t))
                cout << parseTable[nt][t] << "\t";
            else
                cout << "-\t";
        }
        cout << "\n";
    }
    return 0;
}
