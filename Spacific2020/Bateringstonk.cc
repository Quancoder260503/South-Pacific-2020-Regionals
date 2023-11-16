#include "bits/stdc++.h"
using namespace std;
const int MAXN = 4e5 + 20; 
int N, C, K;
int64_t lazy[MAXN], tree[MAXN];
void push_down(int p)
{
    if (lazy[p] != 0)
    {
        lazy[2 * p]      = max(lazy[2 * p], lazy[p]);
        lazy[2 * p + 1]  = max(lazy[2 * p + 1], lazy[p]);
        tree[2 * p]      = max(tree[2 * p], lazy[p]); 
        tree[2 * p + 1]  = max(tree[2 * p + 1], lazy[p]);
        lazy[p] = 0;
    }
    return;
}
void update(int64_t val, int L, int R, int l = 0, int r = K, int p = 1)
{
    if (L > r || R < l) return;
    if (L <= l && r <= R)
    {
        tree[p] = max(tree[p], val);
        lazy[p] = max(lazy[p], val);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    update(val, L, R, l, mid, 2 * p);
    update(val, L, R, mid + 1, r, 2 * p + 1); 
}
int64_t query(int pos, int l = 0, int r = K, int p = 1)
{
    if(l == r)
    {
        return tree[p]; 
    }
    push_down(p); 
    int mid = (l + r) / 2;
    return (pos <= mid ? query(pos, l, mid, 2 * p) : query(pos, mid + 1, r, 2 * p + 1)); 
}
signed main(void)
{
    while (cin >> N >> C >> K)
    {
        vector<vector<int64_t>> dyn(2, vector<int64_t>(K + 1, 0));
        vector<int64_t> F(N + 1);
        vector<int64_t> P(N + 1);
        for (int i = 1; i <= N; i++) cin >> P[i] >> F[i];
        dyn[0][0] = C * 100;
        for (int k = 0; k < N; k++)
        {
            memset(tree, 0, sizeof(tree));
            memset(lazy, 0, sizeof(lazy)); 
            int64_t max_so_far = 0;
            for (int i = 0; i <= K; i++)
            {
                dyn[(k + 1) & 1][i] = max(dyn[(k + 1) & 1][i], max_so_far - i * P[k + 1] * (100 + F[k + 1]));
                max_so_far = max(max_so_far, dyn[k & 1][i] + 1LL * i * P[k + 1] * (100 + F[k + 1]));
                int L = ceil(i - dyn[k & 1][i] / (1.0 * F[k + 1] * P[k + 1])); 
                int R = i; 
                update(dyn[k & 1][i] + 1LL * i * (100 - F[k + 1]) * P[k + 1], L, R); 
            }
            for(int i = 0; i <= K; i++)
            {
                dyn[(k + 1) & 1][i] = max(dyn[(k + 1) & 1][i], query(i) - 1LL * i * (100 - F[k + 1]) * P[k + 1]);
            }
        }
        int64_t ret = 0;
        for (int i = 0; i <= K; i++)
        {
            ret = max(ret, dyn[N & 1][i]);
        }
        cout << ret << '\n';
    }
    return 0;
} 