#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
set<string> terminals;
set<string> nonTerminals;

bool isTerminal(string s) {
    return terminals.count(s);
}

set<string> findFirst(string symbol) {
    if (isTerminal(symbol)) {
        return {symbol};
    }

    if (FIRST.count(symbol)) return FIRST[symbol];

    set<string> result;

    for (string prod : productions[symbol]) {
        if (prod == "eps") {
            result.insert("eps");
            continue;
        }

        vector<string> symbols;
        for (int i = 0; i < prod.size(); i++) {
            string ch(1, prod[i]);
            symbols.push_back(ch);
        }

        bool epsilonInAll = true;

        for (string s : symbols) {
            set<string> temp = findFirst(s);
            for (string t : temp)
                if (t != "eps") result.insert(t);

            if (temp.find("eps") == temp.end()) {
                epsilonInAll = false;
                break;
            }
        }

        if (epsilonInAll) result.insert("eps");
    }

    return FIRST[symbol] = result;
}

int main() {
    productions["E"]  = {"TE'"};
    productions["E'"] = {"+TE'", "eps"};
    productions["T"]  = {"FT'"};
    productions["T'"] = {"*FT'", "eps"};
    productions["F"]  = {"(E)", "id"};

    nonTerminals = {"E", "E'", "T", "T'", "F"};
    terminals = {"+", "*", "(", ")", "id"};

    for (string nt : nonTerminals) {
        set<string> firstSet = findFirst(nt);
        cout << "FIRST(" << nt << ") = { ";
        for (auto x : firstSet) cout << x << " ";
        cout << "}" << endl;
    }
    return 0;
}
