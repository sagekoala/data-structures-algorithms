#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Global variables
int n, p;

void solve(int idx, vector<string>& words, vector<vector<string>>& subsets) {
    if (idx == n) {
        for (int i = 0; i < p; i++) {
            cout << "subset " << i + 1 << ": {";
            for (int j = 0; j < subsets[i].size(); j++) {
                if (j > 0) cout << ",";
                cout << subsets[i][j];
            }
            cout << "}" << endl;
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < p; i++) {
        // tomar la decision
        subsets[i].push_back(words[idx]);

        // llamada recursiva
        solve(idx + 1, words, subsets);

        // deshacer la decision
        subsets[i].pop_back();
    }
}

int main() {
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];

    cin >> p;
    vector<vector<string>> subsets(p);

    solve(0, words, subsets);
    return 0;
}