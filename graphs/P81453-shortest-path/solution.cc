#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Global variables
int n, m;

int main() {
    while (cin >> n >> m) {
        vector<vector<int>> adj(n);
        vector<vector<int>> revAdj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;

            // Directed graph, edge u->v (for reverse adj list, v->u)
            adj[u].push_back(v);
            revAdj[v].push_back(u);
        }

        vector<int> dist(n, -1);
        queue<int> q;
        q.push(n-1);
        dist[n-1] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : revAdj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        vector<int> path;
        int curr = 0;
        while (curr != n-1) {
            path.push_back(curr);

            int best = -1; // to ensure lexigraphically smallest
            for (int v : adj[curr]) {
                if (dist[v] == dist[curr] - 1) {
                    if (best == -1 || v < best) best = v;
                }
            }
            curr = best;
        }
        path.push_back(n-1);

        for (int i = 0; i < path.size(); i++) {
            if (i > 0) cout << " ";
            cout << path[i];
        }
        cout << endl;
    }
    return 0;
}