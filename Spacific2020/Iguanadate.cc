#include "bits/stdc++.h"
using namespace std;
const int M = 1002;
char g[M][M];
int n;
set<pair<int, int>> adj[M * M];
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int vis[M * M];
int visg[M][M]; 
int dyn[M][M]; 
vector<int> topo;
int to(int i, int j, int dir)
{
  return 4 * (i * n + j) + dir;
}
bool valid(int i, int j)
{
  return (0 <= i && i < n && 0 <= j && j < n && g[i][j] != '#');
}
void dfs(int u)
{
  vis[u] = 1;
  for (auto [_, v] : adj[u])
  {
    if (vis[v])
      continue;
    dfs(v);
  }
  topo.push_back(u);
}
void calc_dist(int sx, int sy)
{
  queue<pair<int, int>> q;
  q.push({sx, sy});
  visg[sx][sy] = 1;
  while (q.size())
  {
    auto [i, j] = q.front();
    q.pop();
    for (int k = 0; k < 4; k++)
    {
      int px = dx[k] + i;
      int py = dy[k] + j;
      if (valid(px, py) && !visg[px][py])
      {
        visg[px][py] = 1;
        dyn[px][py] = dyn[i][j] + 1;
        q.push({px, py});
      }
    }
  }
}
signed main(void)
{
  clock_t tStart = clock();
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> g[i][j];
    }
  }
  int ret = 0;
  int N = n * n * 4;
  vector<int> dist(N);
  calc_dist(n - 1, n - 1);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (g[i][j] == '#')
        continue;
      if (i == n - 1 && j == n - 1)
        continue;
      for (int k = 0; k < 4; k++)
      {
        int px = dx[k] + i;
        int py = dy[k] + j;
        if (valid(px, py))
        {
          for (int p = 0; p < 4; p++)
          {
            adj[to(i, j, p)].insert({-dyn[px][py], to(px, py, k)});
          }
        }
      }
    }
  }
  dfs(to(0, 0, 0));
  reverse(topo.begin(), topo.end());
  for (int i = 0; i < topo.size(); i++)
  {
    int u = topo[i];
    for (auto [_, v] : adj[u])
    {
      dist[v] = max(dist[v], dist[u] + 1);
    }
  }
  for (int i = 0; i < 4; i++)
  {
    ret = max(ret, dist[to(n - 1, n - 1, i)]);
  }
  cout << ret + 1 << '\n';
  //printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
  return 0;
}
// 0 : South
// 1 : North
// 2 : West
// 3 : East