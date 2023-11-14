#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;

int n, m, k, f[MAXN], d[MAXN][MAXN], p[MAXN][MAXN], q[MAXN][MAXN], cnt, ans[MAXN][MAXN];
bool vis[MAXN][MAXN];

// This function performs a depth-first search on the states of the DFA.
void dfs(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < m; i++) {
        int xx = d[x][i], yy = d[y][i];
        if (!vis[xx][yy]) dfs(xx, yy);
    }
}

int main() {
    // Read in the number of states, symbols, and final states.
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        f[x] = 1;
    }

    // Read in the DFA transition table.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> d[i][j];
        }
    }

    // Initialize the partition P0.
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((f[i] && !f[j]) || (!f[i] && f[j])) {
                p[i][j] = p[j][i] = 1;
            }
        }
    }

    // Use the partitioning algorithm to minimize the DFA.
    while (true) {
        bool flag = false;
        memset(q, 0, sizeof(q));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!p[i][j]) {
                    for (int l = 0; l < m; l++) {
                        int x = d[i][l], y = d[j][l];
                        if (p[x][y]) {
                            p[i][j] = p[j][i] = 1;
                            flag = true;
                            break;
                        }
                    }
                }
            }
        }
        if (!flag) break;
    }

    // Construct the minimized DFA.
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!p[i][j]) {
                ans[i][j] = ans[j][i] = 1;
            }
        }
    }

    // Perform a depth-first search on the states of the minimized DFA.
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!ans[i][j]) {
                dfs(i, j);
            }
        }
    }

    // Check if the minimized DFA is connected.
    for (int i = 0; i < n; i++) {
        if (!vis[i][i]) {
            for (int j = i + 1; j < n; j++) {
                if (vis[j][j] && !vis[i][j]) {
                    cout << "Error: DFA is not connected" << endl;
                    return 0;
                }
            }
        }
    }

    // Count the number of distinct states in the minimized DFA.
    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i][i]) continue;
        for (int j = i + 1; j < n; j++) {
            if (vis[j][j] && !vis[i][j]) {
                cnt++;
            }
        }
    }

    // Output the minimized DFA.
    cout << cnt << endl;
    for (int i = 0; i < n; i++) {
        if (!vis[i][i]) continue;
        for (int j = i + 1; j < n; j++) {
            if (vis[j][j] && !vis[i][j]) {
                cout << i << " " << j << endl;
            }
        }
    }

    return 0;
}

