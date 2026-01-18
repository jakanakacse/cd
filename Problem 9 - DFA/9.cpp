#include <bits/stdc++.h>
using namespace std;

int main() {
    string input;
    cout << "Enter input: ";
    cin >> input;
    int state = 0;

    for (char ch : input) {
        if (state == 0) {
            if (isalpha(ch) || ch == '_')
                state = 1;
            else if (isdigit(ch))
                state = 2;
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                     ch == '=' || ch == '<' || ch == '>')
                state = 3;
            else
                state = -1;
        }
        else if (state == 1) {
            if (isalnum(ch) || ch == '_')
                state = 1;
            else
                state = -1;
        }
        else if (state == 2) {
            if (isdigit(ch))
                state = 2;
            else
                state = -1;
        }
        else if (state == 3) {
            state = -1;
        }

        if (state == -1)
            break;
    }

    if (state == 1)
        cout << "Identifier\n";
    else if (state == 2)
        cout << "Constant\n";
    else if (state == 3)
        cout << "Operator\n";
    else
        cout << "Invalid token\n";

    return 0;
}
