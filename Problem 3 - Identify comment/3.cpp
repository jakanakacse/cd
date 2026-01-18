#include<bits/stdc++.h>
using namespace std;

int main()
{
    string line;
    cout << "Enter a line: ";
    getline(cin, line);
    
    int i = 0;
    while(i < line.size() && isspace(line[i])) {
        i++;
    }
    
    if(i < line.size() - 1 && line[i] == '/' && line[i + 1] == '/') {
        cout << "This is a single-line comment" << endl;
    } else if(i < line.size() - 1 && line[i] == '/' && line[i+1] == '*') {
        cout << "This is a multi-line comment" << endl;
    } else {
        cout << "This is not a comment" << endl;
    }
}