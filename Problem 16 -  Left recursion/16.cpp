#include <bits/stdc++.h>
using namespace std;

void eliminateLeftRecursion(string nonTerminal, vector<string> productions) {
    vector<string> alpha;
    vector<string> beta;

    for (string prod : productions) {
        if (prod[0] == nonTerminal[0]) {
            alpha.push_back(prod.substr(1));
        } else {
            beta.push_back(prod);
        }
    }

    if (alpha.empty()) {
        cout << "No left recursion in " << nonTerminal << endl;
        return;
    }

    string newNT = nonTerminal + "'";

    cout << nonTerminal << " -> ";
    for (int i = 0; i < beta.size(); i++) {
        cout << beta[i] << newNT;
        if (i != beta.size() - 1) cout << " | ";
    }
    cout << endl;

    cout << newNT << " -> ";
    for (int i = 0; i < alpha.size(); i++) {
        cout << alpha[i] << newNT << " | ";
    }
    cout << "eps" << endl << endl;
}

int main() {
    cout << "Eliminating Left Recursion:\n\n";

    eliminateLeftRecursion("A", {"Aabb", "BC"});
    eliminateLeftRecursion("B", {"Bca", "C"});

    return 0;
}
