#include <bits/stdc++.h>
using namespace std;

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    int state = 0;

    for (char ch : input) {
        if (state == 0) {
            if (isalpha(ch) || ch == '_')
                state = 1;
            else {
                state = -1;
                break;
            }
        }
        else if (state == 1) {
            if (isalnum(ch) || ch == '_')
                state = 1;
            else {
                state = -1;
                break;
            }
        }
    }
    if (state == 1)
        cout << "Valid Identifier" << endl;
    else
        cout << "Invalid Identifier" << endl;
    return 0;
}
