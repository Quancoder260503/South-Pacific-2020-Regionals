#include "bits/stdc++.h"
using namespace std;
const int MAXN = 20000;
struct Matching
{
    int n;
    vector<vector<int>> ke;
    vector<int> seen;
    vector<int> matchL, matchR;
    int iteration;
    Matching(int _n) : n(_n), ke(_n), seen(_n, false), matchL(_n, -1), matchR(_n, -1), iteration{0}
    {
    }
    void addEdge(int u, int v)
    {
        ke[u].push_back(v);
    }
    bool dfs(int u)
    {
        seen[u] = iteration;
        for (int v : ke[u])
        {
            if (matchR[v] < 0)
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u])
        {
            if (seen[matchR[v]] != iteration && dfs(matchR[v]))
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match()
    {
        int res = 0;
        int newMatches = 0;
        do
        {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++)
            {
                if (matchL[u] < 0 && dfs(u))
                    ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};
int n, m;
struct edge
{
    int from, to;
} Edge[MAXN];
vector<int>adj[MAXN]; 
int vis[MAXN];
void dfs(int u)
{
    vis[u] = 1; 
    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i]; 
        if(vis[v]) continue; 
        dfs(v); 
    }
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> Edge[i].to >> Edge[i].from;
    }
    Matching mcbm(m + 1);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == j) continue;
            if (Edge[i].to == Edge[j].from)
            {
                adj[i].push_back(j); 
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        fill(vis, vis + m + 1, 0); 
        dfs(i); 
        for(int j = 0; j < m; j++)
        {
            if(i == j || !vis[j]) continue;
            mcbm.addEdge(i, j);  
        }
    }
    cout << m - mcbm.match() << '\n'; 
    return 0;
}