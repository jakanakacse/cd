#include<bits/stdc++.h>
using namespace std;

bool isKeyword(const string &str) {
    string keywords[] = {"int", "float", "if", "else", "while", "return"};
    for (string k : keywords)
        if (str == k)
            return true;
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    char ch;
    string token;

    while (cin.get(ch)) {
        if (isspace(ch))
            continue;

        if (ch == '/' && cin.peek() == '/') {
            while (cin.get(ch) && ch != '\n');
            continue;
        }

        if (ch == '/' && cin.peek() == '*') {
            cin.get(ch);
            while (cin.get(ch)) {
                if (ch == '*' && cin.peek() == '/') {
                    cin.get(ch);
                    break;
                }
            }
            continue;
        }

        if (isalpha(ch)) {
            token = ch;
            while (isalnum(cin.peek())) {
                cin.get(ch);
                token += ch;
            }

            if (isKeyword(token))
                cout << token << " : Keyword\n";
            else
                cout << token << " : Identifier\n";
        }

        else if (isdigit(ch)) {
            token = ch;
            while (isdigit(cin.peek())) {
                cin.get(ch);
                token += ch;
            }
            cout << token << " : Number\n";
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>') {
            cout << ch << " : Operator\n";
        }

        else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}') {
            cout << ch << " : Separator\n";
        }
    }

    return 0;
}
