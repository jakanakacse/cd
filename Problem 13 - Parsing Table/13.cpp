#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
vector<string> nonTerminals = {"E", "E'", "T", "T'", "F"};
vector<string> terminals = {"id", "+", "*", "(", ")", "$"};

map<string, map<string, string>> parseTable;

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
    if (!temp.empty()) symbols.push_back(temp);
    return symbols;
}

set<string> getFirstOfString(string alpha) {
    set<string> result;
    if (alpha == "eps") {
        result.insert("eps");
        return result;
    }

    vector<string> symbols = splitSymbols(alpha);
    bool allEps = true;
    for (string sym : symbols) {
        if (FIRST.count(sym)) {
            set<string> f = FIRST[sym];
            for (string s : f)
                if (s != "eps") result.insert(s);
            if (f.find("eps") == f.end()) {
                allEps = false;
                break;
            }
        } else {
            result.insert(sym);
            allEps = false;
            break;
        }
    }
    if (allEps)
        result.insert("eps");
    return result;
}

int main() {
    productions["E"]  = {"T E'"};
    productions["E'"] = {"+ T E'", "eps"};
    productions["T"]  = {"F T'"};
    productions["T'"] = {"* F T'", "eps"};
    productions["F"]  = {"( E )", "id"};

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

    for (string nt : nonTerminals) {
        for (string prod : productions[nt]) {
            set<string> firstSet = getFirstOfString(prod);

            for (string t : firstSet) {
                if (t != "eps")
                    parseTable[nt][t] = prod;
            }

            if (firstSet.find("eps") != firstSet.end()) {
                for (string f : FOLLOW[nt]) {
                    parseTable[nt][f] = prod;
                }
            }
        }
    }

    cout << "\nLL(1) Parsing Table:\n\n";
    cout << "\t";
    for (string t : terminals) cout << t << "\t";
    cout << "\n";

    for (string nt : nonTerminals) {
        cout << nt << "\t";
        for (string t : terminals) {
            if (parseTable[nt].count(t))
                cout << parseTable[nt][t] << "\t";
            else
                cout << "-\t";
        }
        cout << "\n";
    }
    return 0;
}
