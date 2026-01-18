#include<bits/stdc++.h>
using namespace std; 

int main()
{
    string identifier;
    cout << "Enter an identifier: ";
    cin >> identifier;

    bool valid = true;

    if(!isalpha(identifier[0]) && identifier[0] != '_') {
        valid = false;
    }

    for(int i = 1; i < identifier.size(); ++i) {
        if(!isalnum(identifier[i]) && identifier[i] != '_') {
            valid = false;
            break;
        }
    }
    
    if(valid) {
        cout << "The given identifier is valid." << endl;
    } else {
        cout << "The given identifier is not valid." << endl;
    }
}