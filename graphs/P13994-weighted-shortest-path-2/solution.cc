#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Global variables
int n, m;

int main() {
    while (cin >> n >> m) {
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;

            // Directed graph, edge from u->v
            adj[u].push_back({c, v});
        }

        int x, y; // x is source, y is the target
        cin >> x >> y;

        vector<int> dist(n, 1e9);
        vector<int> parent(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, x}); // start with target, dist to target is 0
        dist[x] = 0;
        while(!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (auto [c, v] : adj[u]) {
                if (dist[v] > dist[u] + c) {
                    dist[v] = dist[u] + c;
                    pq.push({dist[v], v});
                    parent[v] = u;
                }
            }
        }

        // Test
        if (dist[y] == 1e9) cout << "no path from " << x << " to " << y << endl;
        else {
            vector<int> path; 
            int curr = y;
            while (curr != -1) {
                path.push_back(curr);
                curr = parent[curr];
            }

            reverse(path.begin(), path.end());

            for (int i = 0; i < path.size(); i++) {
                if (i > 0) cout << " ";
                cout << path[i];
            }
            cout << endl;
        }
    }
    return 0;
}