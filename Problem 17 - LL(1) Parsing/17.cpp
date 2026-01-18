#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
map<string, map<string, string>> parseTable;

vector<string> nonTerminals = {"E", "E'", "T", "T'", "F"};
vector<string> terminals = {"id", "+", "*", "(", ")", "$"};

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
    if (alpha == "eps") { result.insert("eps"); return result; }

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
    if (allEps) result.insert("eps");
    return result;
}

void buildParsingTable() {
    for (string nt : nonTerminals) {
        for (string prod : productions[nt]) {
            set<string> firstSet = getFirstOfString(prod);

            for (string t : firstSet)
                if (t != "eps") parseTable[nt][t] = prod;

            if (firstSet.find("eps") != firstSet.end()) {
                for (string f : FOLLOW[nt]) parseTable[nt][f] = prod;
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

    buildParsingTable();

    string input;
    cout << "Enter input string (with $ at end): ";
    cin >> input;

    stack<string> st;
    st.push("$");
    st.push("E");

    int index = 0;

    cout << "\nParsing Steps:\n";

    while (!st.empty()) {
        string X = st.top();

        string a;
        bool matched = false;
        for (string t : terminals) {
            if (input.substr(index, t.size()) == t) {
                a = t;
                matched = true;
                break;
            }
        }
        if (!matched) {
            cout << "Error! Unknown input symbol.\n";
            break;
        }

        cout << "Stack top: " << X << ", Input symbol: " << a << "\n";

        if (X == "$" && a == "$") {
            cout << "String Accepted!\n";
            break;
        } else if (X == a) {
            st.pop();
            index += a.size();
        } else if (parseTable[X].count(a)) {
            st.pop();
            string prod = parseTable[X][a];
            if (prod != "eps") {
                vector<string> symbols = splitSymbols(prod);
                for (int i = symbols.size() - 1; i >= 0; i--)
                    st.push(symbols[i]);
            }
        } else {
            cout << "Error! String Rejected.\n";
            break;
        }
    }
    return 0;
}
