#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Global variables
int n, m;

int main() {
    while (cin >> n >> m) {
        vector<vector<pair<int, int>>> adj(n); // {cost, vertex}
        int totalCost = 0;
        for (int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;

            totalCost+=c;

            // Undirected graph, u->v and v->u
            if (u != v) {
                adj[u].push_back({c, v}); // {cost, vertex}
                adj[v].push_back({c, u});
            }
        }

        vector<bool> inMST(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int totalMST = 0;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (!inMST[u]) {
                inMST[u] = true;
                totalMST+=d;
            }

            for (auto [c, v] : adj[u]) {
                if (!inMST[v]) {
                    pq.push({c, v});
                }
            }
        }

        cout << totalCost - totalMST << endl;

    }
    return 0;
}