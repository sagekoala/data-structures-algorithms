#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Global variables
int n, m;
int num;

// Struct to track position AND distance
struct Node {
    int r;
    int c;
    int dist;
};

// Directional vectors
vector<int> dr = {-1, 1, 0, 0};
vector<int> dc = {0, 0, -1, 1};

void bfs(int startR, int startC, vector<vector<char>>& board, vector<vector<bool>>& visited) {
    queue<pair<int, int>> q;
    q.push({startR, startC});
    visited[startR][startC] = true;
    
    while (!q.empty()) {
        auto [currR, currC] = q.front();
        q.pop();

        if (board[currR][currC] == 't') num++;

        for (int i = 0; i < 4; i++) {
            int newR = currR + dr[i];
            int newC = currC + dc[i];

            if (newR >= 0 && newR < n && newC >= 0 && newC < m && board[newR][newC] != 'X' && !visited[newR][newC]) {
                q.push({newR, newC});
                visited[newR][newC] = true;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int startR, startC;
    cin >> startR >> startC;
    startR--;
    startC--;

    num = 0;
    bfs(startR, startC, board, visited);
    cout << num << endl;
    return 0;
}

