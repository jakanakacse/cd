#include <bits/stdc++.h>
using namespace std;

string commonPrefix(string a, string b) {
    string prefix = "";
    int len = min(a.length(), b.length());
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) break;
        prefix += a[i];
    }
    return prefix;
}

void leftFactor(string nonTerminal, vector<string> productions) {
    map<string, vector<string>> groups;
    for (string prod : productions) {
        string key(1, prod[0]);
        groups[key].push_back(prod);
    }

    bool factored = false;
    string newNT = nonTerminal + "'";

    cout << nonTerminal << " -> ";

    for (auto group : groups) {
        if (group.second.size() > 1) {
            string prefix = group.second[0];
            for (int i = 1; i < group.second.size(); i++)
                prefix = commonPrefix(prefix, group.second[i]);

            cout << prefix << newNT << " | ";
            factored = true;

            cout << "\n" << newNT << " -> ";
            for (int i = 0; i < group.second.size(); i++) {
                string suffix = group.second[i].substr(prefix.length());
                if (suffix == "")
                    cout << "eps";
                else
                    cout << suffix;

                if (i != group.second.size() - 1)
                    cout << " | ";
            }
        } else {
            cout << group.second[0] << " | ";
        }
    }
    cout << endl;
    if (!factored)
        cout << "No left factoring needed.\n";
}

int main() {
    cout << "Left Factoring Result:\n\n";
    leftFactor("A", {"abc", "abd", "aef", "b"});
}
