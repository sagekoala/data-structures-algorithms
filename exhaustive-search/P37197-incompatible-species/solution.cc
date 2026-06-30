#include <iostream>
#include <vector>

using namespace std;

// Global variabls
int n, m;
string result;

// idx tracks which letter were on, idx == n base case
void solve(int idx, vector<char>& species, vector<bool>& used, vector<vector<bool>>& incompat) {
    if (idx == n) {
        cout << result << endl;
        return;
    }
 
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        if (idx > 0 && incompat[(int)result[idx-1]][(int)species[i]]) continue;

        // tomar la decision
        result.push_back(species[i]);
        used[i] = true;

        // llamada recursiva 
        solve(idx + 1, species, used, incompat);

        // deshacer la decision
        result.pop_back();
        used[i] = false;
    }
}

int main() {
    cin >> n;
    vector<char> species(n);
    for (int i = 0; i < n; i++) {
        cin >> species[i];
    }

    // Used vector
    vector<bool> used(n, false);

    // ascii 128 x 128
    vector<vector<bool>> incompat(128, vector<bool>(128, false));

    cin >> m;
    for (int i = 0; i < m; i++) {
        string pair;
        cin >> pair;

        char a = pair[0], b = pair[1];
        incompat[(int)a][(int)b] = true;
        incompat[(int)b][(int)a] = true;
    }

    solve(0, species, used, incompat);
    return 0;
} 