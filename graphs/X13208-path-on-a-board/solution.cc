#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Directional vectors
vector<int> dr = {-1, 1, 0, 0};
vector<int> dc = {0, 0, -1, 1};

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> grid(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        vector<vector<int>> dist(n, vector<int>(n, 1e9));

        // Start from middle
        int startR = n / 2, startC = n /2;
        dist[startR][startC] = grid[startR][startC];
        
        // Priority queue, push the starting cost, and coordinates {cost, r, c}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({grid[startR][startC], startR, startC});
        while (!pq.empty()) {
            auto [d, r, c] = pq.top();
            pq.pop();

            // If we cannot achieve lower dist with this d, continue forward
            if (d > dist[r][c]) continue;

            // If at an edge, cout d and break
            if (r == 0 || r == n - 1 || c == 0 || c == n - 1) {
                cout << d << endl;
                break;
            }

            // Explore neighbors
            for (int i = 0; i < 4; i++) {
                int newR = r + dr[i];
                int newC = c + dc[i];

                // If in bounds
                if (newR >= 0 && newR < n && newC >= 0 && newC < n) {
                    int newD = d + grid[newR][newC]; 
                    if (dist[newR][newC] > newD) {
                        dist[newR][newC] = newD;
                        pq.push({newD, newR, newC});
                    }
                }
            }
        }
    }
    return 0;
} 