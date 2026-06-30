#include <iostream>
#include <vector>

using namespace std;

// Global variables
int x, n;
int ways;

// if idx == n 
void solve(int idx, int remainder, vector<int>& coins) {
    if (remainder < 0) return;

    if (idx == n) {
        if (remainder == 0) ways++;
        return;
    }

    for (int k = 0; k <= 2; k++) {
        if (remainder - k*coins[idx] < 0) continue;
        solve(idx + 1, remainder - k*coins[idx], coins);
    }
}

int main() {
    while (cin >> x >> n) {
        vector<int> coins(n);
        for (int i = 0; i < n; i++) cin >> coins[i];

        ways = 0;
        solve(0, x, coins);
        cout << ways << endl;
    }
    return 0;
}