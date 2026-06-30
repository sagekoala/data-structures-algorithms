#include <iostream>
#include <vector>

using namespace std;

int M[10][10]; // 1-indexed, sized to allow digits [1-9][1-9]
bool used[10];

// Global variables
int m, n;
int best;

// Position tracks num digits we have, 
void solve(int pos, int rem, int prevDig, int prize) {

    if (pos == n) {
        best = max(best, prize);
        return;
    }

    for (int num = 1; num <= n; num++) {
        if (used[num]) continue;

        int newRem = (rem*10+num) %m;
        if (newRem == 0) continue;

        int addedPrize;
        if (pos>0) addedPrize = M[prevDig][num];
        else addedPrize = 0;

        // Tomar la decision
        used[num] = true;

        // llamada recursiva
        solve(pos + 1, newRem, num, addedPrize + prize);

        // Deshacer la decision
        used[num] = false;
    }
}

int main() {
    while (cin >> m >> n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> M[i][j];
            }
        }
    

        for (int i = 0; i < 10; i++) used[i] = false;

        best = 0;
        solve(0, 0, 0, 0);
        cout << best << endl;
    }
    return 0;
}