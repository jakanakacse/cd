#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> productions;
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
map<string, map<string, string>> parseTable;

vector<string> nonTerminals = {"E", "E'", "T", "T'", "F"};
vector<string> terminals = {"id", "+", "*", "(", ")", "$"};

set<string> getFirstOfString(const string &alpha) {
    set<string> result;
    if (alpha == "eps") { result.insert("eps"); return result; }

    for (int i = 0; i < alpha.size(); i++) {
        string sym(1, alpha[i]);
        if (FIRST.count(sym)) {
            set<string> f = FIRST[sym];
            for (auto s : f) if (s != "eps") result.insert(s);
            if (f.find("eps") == f.end()) break;
        } else {
            result.insert(sym); break;
        }
    }
    return result;
}

void buildParsingTable() {
    for (auto nt : nonTerminals) {
        for (auto prod : productions[nt]) {
            set<string> firstSet = getFirstOfString(prod);

            for (auto t : firstSet)
                if (t != "eps") parseTable[nt][t] = prod;

            if (firstSet.find("eps") != firstSet.end()) {
                for (auto f : FOLLOW[nt]) parseTable[nt][f] = prod;
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
    string a = string(1, input[index]);

    cout << "\nParsing Steps:\n";

    while (!st.empty()) {
        string X = st.top();
        a = string(1, input[index]);

        cout << "Stack top: " << X << ", Input symbol: " << a << "\n";

        if (X == "$" && a == "$") {
            cout << "String Accepted!\n";
            break;
        } else if (X == a) {
            st.pop();
            index++;
        } else if (parseTable[X].count(a)) {
            st.pop();
            string prod = parseTable[X][a];
            if (prod != "eps") {
                for (int i = prod.size() - 1; i >= 0; i--)
                    st.push(string(1, prod[i]));
            }
        } else {
            cout << "Error! String Rejected.\n";
            break;
        }
    }
    return 0;
}
