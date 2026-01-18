#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions;

void leftmostDerivation(char start, string input) {
    string sentential = "";
    sentential += start;
    cout << "Start: " << sentential << "\n";
    int step = 1;
    while (sentential != input) {
        bool replaced = false;
        for (int i = 0; i < sentential.size(); i++) {
            char symbol = sentential[i];
            if (productions.count(symbol)) {
                string prod = productions[symbol][0];
                if (prod == "eps")
                    sentential.erase(i, 1);
                else
                    sentential.replace(i, 1, prod);
                cout << "Step " << step++ << ": " << sentential << "\n";
                replaced = true;
                break;
            }
        }
        if (!replaced) break;
    }
}

int main() {
    productions['E']  = {"TE'"};
    productions['E\''] = {"+TE'", "eps"};
    productions['T']  = {"FT'"};
    productions['T\''] = {"*FT'", "eps"};
    productions['F']  = {"(E)", "id"};

    char startSymbol = 'E';
    string input;
    cout << "Enter input string to derive: ";
    cin >> input;

    cout << "\nLeftmost Derivation:\n";
    leftmostDerivation(startSymbol, input);

    return 0;
}
