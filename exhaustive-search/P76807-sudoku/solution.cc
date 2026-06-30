#include <iostream>
#include <vector>

using namespace std;

// Global variables
bool usedR[9][10];
bool usedC[9][10];
bool usedB[9][10];

bool solve(vector<vector<char>>& board) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') {
                int b = (r/3)*3 + c/3;
                for (int num = 1; num <= 9; num++) {
                    if (!usedR[r][num] && !usedC[c][num] && !usedB[b][num]) {
                        // tomar la decision
                        board[r][c] = '0' + num;
                        usedR[r][num] = true;
                        usedC[c][num] = true;
                        usedB[b][num] = true;

                        if (solve(board)) return true;

                        // deshacer la decision
                        // tomar la decision
                        board[r][c] = '.';
                        usedR[r][num] = false;
                        usedC[c][num] = false;
                        usedB[b][num] = false;
                    }
                }
                // if no digit worked, return false
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    cout << n << endl;

    for (int game = 0; game < n; game ++) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 10; j++) {
                usedC[i][j] = usedR[i][j] = usedB[i][j] = false;
            }
        }

        vector<vector<char>> board(9, vector<char>(9));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> board[i][j];

                if (board[i][j] != '.') {
                    int d = board[i][j] - '0';
                    usedR[i][d] = true;
                    usedC[j][d] = true;
                    usedB[(i/3)*3 + j/3][d] = true; 
                }
            }
        }

        solve(board);
        cout << endl;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (j > 0) cout << " ";
                cout << board[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}