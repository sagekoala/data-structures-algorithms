#include <iostream>
#include <vector>

using namespace std;

// Global variables
int n, m;
bool hasCycle;

void dfs(int u, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, u, adj, visited);
        } else if (v != parent) {
            hasCycle = true;
        }
    }
}

int main() {
    while (cin >> n >> m) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;

            // Undirected graph: edge u->v AND edge v->u
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n, false);
        
        hasCycle = false;
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, -1, adj, visited);
                components++;
            }
        }

        if (!hasCycle) cout << components << endl;
        else cout << "no" << endl;
    }
    return 0;
}