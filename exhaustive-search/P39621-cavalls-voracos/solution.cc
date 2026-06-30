#include <iostream>
#include <vector>

using namespace std;

// Global variables
int n, m;
int best;

// Directional vectors
vector<int> dr = {-2, -2, -1, -1, 1, 1, 2, 2};
vector<int> dc = {-1, 1, -2, 2, -2, 2, -1, 1};

bool isAttacked(int r, int c, vector<vector<bool>>& hasKnight) {
    for (int i = 0; i < 8; i++) {
        int newR = r + dr[i];
        int newC = c + dc[i];

        // if in bounds BUT has knight placed, return true i.e. is attacked
        if (newR >= 0 && newR < n && newC >= 0 && newC < m && hasKnight[newR][newC]) {
            return true;
        }
    }
    return false;
}

// idx tracks which cell we're on, idx == n*m base case
void solve(int idx, int currSum, vector<vector<int>>& board, vector<vector<bool>>& hasKnight, vector<int>& suffixSum) {
    // Pruning
    if (currSum + suffixSum[idx] <= best) return;

    // Base case
    if (idx == n*m) {
        best = max(best, currSum);
        return;
    }

    // Option 1: if not attacked and knight not currently placed, place a knight
    int r = idx / m, c = idx % m;
    if (!isAttacked(r, c, hasKnight) && !hasKnight[r][c]) {
        // Tomar la decision
        hasKnight[r][c] = true;

        // llamada recursiva
        solve(idx + 1, currSum + board[r][c], board, hasKnight, suffixSum);

        // Deshacer la decision
        hasKnight[r][c] = false;
    }

    // Option 2: Advance the index without placing a knight
    solve(idx + 1, currSum, board, hasKnight, suffixSum);
} 

int main() {
    while (cin >> n >> m) {

        // Read input into the board
        vector<vector<int>> board(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> board[i][j];
            }
        }

        vector<vector<bool>> hasKnight(n, vector<bool>(m, false));
        
        // Create a suffixSum list to be able to prune later
        vector<int> suffixSum(n*m+1);
        suffixSum[n*m] = 0;
        for (int k = n*m-1; k >= 0; --k) {
            int r = k/m, c = k%m;
            suffixSum[k] = suffixSum[k+1] + board[r][c];
        }

        best = 0;
        solve(0, 0, board, hasKnight, suffixSum);
        cout << best << endl;
    }
    return 0;
}