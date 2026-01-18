#include<bits/stdc++.h>
using namespace std;

int main()
{
    string op;
    cout << "Enter a operator: ";
    cin >> op;

    string operators[] = {"+", "-", "*", "/", "%", 
                        "==", "!=", ">", "<", ">=", "<=", 
                        "&&", "||", "!", "=", 
                        "|", "&", "~", "^",
                        "++", "--"}; 
    string name[] = {"addition", "subtraction", "multiplication", "division", "modulus", 
                    "equal to", "not equal to", "greater than", "less than",  "greater or equal than", "less or equal than",
                    "and", "or", "not", "assignment",
                    "logical or", "logical and", "negation", "xor",
                    "increment", "decrement"};
    bool f = false;

    int i = 0;
    for(string s : operators) {
        if(s == op) {
            f = true;
            break;
        }
        i++;
    }

    if(f) {
        cout << op << " is " << name[i] << " operator";
    } else {
        cout << op << " is not a valid operator";
    }
}