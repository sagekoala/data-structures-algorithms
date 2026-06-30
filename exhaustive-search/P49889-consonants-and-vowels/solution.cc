#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Global variables
int n;
string result;

// Idx tracks which letter were on, idx == 2n base case
void solve(int idx, vector<char>& cons, vector<char>& vowels, vector<bool>& usedC, vector<bool>& usedV) {
    if (idx == 2*n) {
        cout << result << endl;
        return;
    }

    if (idx % 2 == 0) {
        // Even idx use available con
        for (int i = 0; i < n; i++) {
            if (!usedC[i]) {
                // tomar la decision
                result.push_back(cons[i]);
                usedC[i] = true;

                // llamada recursiva
                solve(idx + 1, cons, vowels, usedC, usedV);

                // deshacer la decision
                result.pop_back();
                usedC[i] = false;
            }
        }
    } else {
        // odd idx, use available vowel
        for (int i = 0; i < n; i++) {
            if (!usedV[i]) {
                // tomar la decision
                result.push_back(vowels[i]);
                usedV[i] = true;

                // llamada recursiva
                solve(idx + 1, cons, vowels, usedC, usedV);

                // deshacer la decision
                result.pop_back();
                usedV[i] = false;
            }
        }
    }
}


int main() {
    cin >> n;
    vector<char> cons(n);
    vector<char> vowels(n);

    for (int i = 0; i < n; i++) cin >> cons[i];
    for (int i = 0; i < n; i++) cin >> vowels[i];

    vector<bool> usedC(n, false);
    vector<bool> usedV(n, false);

    solve(0, cons, vowels, usedC, usedV);
    return 0;
}