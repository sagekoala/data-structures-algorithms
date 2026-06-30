#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<string> tasks(n);
        for (int i = 0; i < n; i++) cin >> tasks[i];
        sort(tasks.begin(), tasks.end()); // sort to meet alphabetically smaller requirement

        // Map each task to an id that corresponds to its position in tasks vector
        unordered_map<string, int> id;
        for (int i = 0; i < n; i++) {
            id[tasks[i]] = i;
        }   

        int m;
        cin >> m;
        vector<vector<int>> adj(n);
        vector<int> inDeg(n, 0);
        for (int i = 0; i < m; i++) {
            string u, v;
            cin >> u >> v;

            // Directed graph   
            adj[id[u]].push_back(id[v]);
            inDeg[id[v]]++; // v has a dependency, increment its inDegree
        }

        priority_queue<int, vector<int>, greater<int>> pq;
        int processed = 0;
        for (int i = 0; i < n; i++) {
            if (inDeg[i] == 0) {
                pq.push(i);
                processed++;
            }
        }

        string output;
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();

            output += tasks[u];

            for (int v : adj[u]) {
                if (--inDeg[v] == 0) {
                    pq.push(v);
                    processed++;
                }
            }
        }

        if (processed == n) cout << output << endl;
        else cout << "NO VALID ORDERING" << endl;

    }
    return 0;
}
 