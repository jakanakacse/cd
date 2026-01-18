#include<bits/stdc++.h>
using namespace std;

bool check(string s)
{
    int i = 0;
    while(i < s.size() && s[i] == 'a') {
        i++;
    }
    if(i == s.size() || s[i] != 'b') {
        return false;
    }
    while(i < s.size() && s[i] == 'b') {
        i++;
    }
    if(i == s.size())  return true;
    else return false;
}

int main()
{
    string s;
    cout << "Enter a string: ";
    cin >> s;

    bool f1 = false, f2 = false, f3 = false;
    if(s == "a") {
        f1 = true;
    }
    if(check(s)) {
        f2 = true;
    }
    if(s == "abb") {
        f3 = true;
    }

    if(!f1 && !f2 && !f3) {
        cout << "No match" << endl;
        return 0;
    }
    if(f1) {
        cout << s << " matches under \"a\"" << endl;
    }
    if(f2) {
        cout << s << " matches under \"a*b+\"" << endl;
    }
    if(f3) {
        cout << s << " matches under \"abb\"" << endl;
    }
}