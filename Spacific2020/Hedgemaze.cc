#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int M = 20;
const int MAXN = 65;
const int mod = 1e9 + 7;
int n;
lint m;
char g[M][M];
int N;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
struct matrix
{
    lint arr[MAXN][MAXN];
    void init()
    {
        memset(arr, 0, sizeof(arr));
    }
    void print()
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << '\n';
        }
    }
    lint get(int col)
    {
        lint ans = 0;
        for (int i = 1; i <= N; i++)
        {
            ans = (ans + mod + arr[i][col]) % mod;
        }
        return ans;
    }
};
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    c.init();
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            for (int k = 1; k <= N; k++)
            {
                c.arr[i][j] = (c.arr[i][j] + 1LL * a.arr[i][k] % mod * b.arr[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
}
int to(int i, int j)
{
    return (i - 1) * n + j;
}
bool valid(int i, int j)
{
    return (1 <= i && i <= n && 1 <= j && j <= n && g[i][j] != '#');
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> g[i][j];
        }
    }
    N = n * n;
    matrix dp, res;
    dp.init(), res.init(); 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (g[i][j] == '#') continue;
            for (int dir = 0; dir < 4; dir++)
            {
                int cnt = 0;
                int curr = dir;
                int px = i + dx[curr];
                int py = j + dy[curr];
                while (!valid(px, py))
                {
                    if (cnt == 4) break;
                    cnt++;
                    curr = (curr + 1) % 4;
                    px = i + dx[curr];
                    py = j + dy[curr];
                }
                if (cnt == 4)
                {
                    dp.arr[to(i, j)][to(i, j)] += 1;
                    if (g[i][j] == '*')
                    {
                        res.arr[to(i, j)][to(i, j)]++;
                    }
                }
                else
                {
                    dp.arr[to(i, j)][to(px, py)] += 1;
                    if (g[i][j] == '*')
                    {
                        res.arr[to(i, j)][to(px, py)]++; 
                    }
                }
            }
        }
    }
    m--;
    while (m)
    {
        if (m & 1)
            res = res * dp;
        dp = dp * dp;
        m = m / 2;
    } 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << res.get(to(i, j)) << " ";
        }
        cout << '\n';
    }
    return 0;
}