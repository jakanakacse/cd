#include <bits/stdc++.h>
using namespace std;

int main() 
{
    cout << "Enter the input string: " << endl;
    string s;
    getline(cin, s);

    vector<string> ops = {"+", "-", "*", "/", "%", 
                          "==", "!=", ">", "<", ">=", "<=", 
                          "&&", "||", "!", "=", 
                          "|", "&", "~", "^",
                          "++", "--"};

    sort(ops.begin(), ops.end(), [](string &a, string &b){
        return a.size() > b.size();
    });

    unordered_map<string,int> counts;
    int total = 0;
    for (int i = 0; i < s.size();) {
        bool matched = false;
        for (auto &op : ops) {
            if (i + op.size() <= s.size() && s.compare(i, op.size(), op) == 0) {
                counts[op]++;
                total++;
                i += op.size();
                matched = true;
                break;
            }
        }
        if (!matched) ++i;
    }

    cout << "Total operators found: " << total << endl;
    for (auto &op : ops) {
        if (counts[op] > 0)
            cout << "'" << op << "' : " << counts[op] << endl;
    }
    return 0;
}