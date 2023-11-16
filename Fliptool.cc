#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e3 + 10;
const int M = 1e6 + 10;
int n, m;
char g[MAXN][MAXN];
bool vis[MAXN][MAXN];
int fa[MAXN][MAXN];
bool del[MAXN];
set<int> adj[M];
int col[M];
int dp[M][2];
int dx[8] = {-1, 1, 0, 0, -1, 1, 1, -1};
int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int N;
void bfs(int sx, int sy)
{
    queue<pair<int, int>> q;
    q.push({sx, sy});
    vis[sx][sy] = 1;
    fa[sx][sy] = N;
    while (q.size())
    {
        int u = q.front().first;
        int v = q.front().second;
        q.pop();
        for (int k = 0; k < 8; k++)
        {
            int tx = u + dx[k];
            int ty = v + dy[k];
            if (tx < 1 || ty < 1 || tx > n || ty > m)
                continue;
            if (vis[tx][ty] || g[tx][ty] != g[sx][sy])
                continue;
            vis[tx][ty] = 1;
            fa[tx][ty] = N;
            q.push({tx, ty});
        }
    }
}
int dep[MAXN]; 
void dfs(int u, int p)
{
     for(auto v : adj[u])
     {
        if(v == p) continue; 
        dep[v] = dep[u] + 1;
        dfs(v, u); 
     }
}
set<pair<int,int>>edge;
signed main(void)
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> g[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!vis[i][j])
            {
                col[++N] = (g[i][j] == 'x');
                bfs(i, j);
            }
        }
    } 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                int tx = i + dx[k];
                int ty = j + dy[k];
                if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
                if (fa[tx][ty] == fa[i][j]) continue;
                adj[fa[i][j]].insert(fa[tx][ty]);
                edge.insert({fa[i][j], fa[tx][ty]}); 
            }
        }
    }
    int ans = 0;
    dfs(1, 0);
    pair<int,int> f = {0, 1};  
    for(int i = 1; i <= N; i++)
    {
       f = max(f, {dep[i], i});     
    }
    dep[f.second] = 0; 
    dfs(f.second, 0);
    for(int i = 1; i <= N; i++)
    {
         ans = max(ans, dep[i]); 
    }
    cout << (ans + 1) / 2 << '\n';
    return 0;
}