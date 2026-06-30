#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Global variables
int n, m;

// Directional vectors
vector<int> dr = {-1, 1, 0 , 0};
vector<int> dc = {0, 0, -1, 1};

int main() {
    while (cin >> n >> m) {
        vector<vector<char>> board(n, vector<char>(m));
        vector<vector<int>> result(n, vector<int>(m, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> board[i][j];

                if (board[i][j] == 'T') {
                    result[i][j] = 0;
                    q.push({i, j});
                }
                if (board[i][j] == 'X') {
                    result[i][j] = -2;
                }
            }
        }

        while (!q.empty()) {
            auto [currR, currC] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int newR = currR + dr[i];
                int newC = currC + dc[i];

                if (newR >= 0 && newR < n && newC >= 0 && newC < m && result[newR][newC] == -1) {
                    result[newR][newC] = result[currR][currC] + 1;
                    q.push({newR, newC});
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j > 0) cout << " ";
                cout << result[i][j];
            }
            cout << endl;
        }
        cout << "----------" << endl;
    }
    
    return 0;
}