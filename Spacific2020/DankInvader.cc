#include "bits/stdc++.h"
using namespace std; 
int N;
struct fenwick
{
    int N;
    vector<int> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int sum(int i)
    {
        int c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    int query(int L, int R)
    {
        if(L > R) return 0; 
        return sum(R) - sum(L - 1); 
    };
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
signed main(void)
{
    while (cin >> N)
    { 
        vector<int>H(N + 1);
        vector<int>ord;
        for(int i = 0; i < N; i++)
        {
            cin >> H[i]; 
            ord.push_back(H[i]); 
        }
        H[N] = INT32_MAX; 
        ord.push_back(H[N]); 
        sort(ord.begin(), ord.end()); 
        ord.erase(unique(ord.begin(), ord.end()), ord.end());
        for(int i = 0; i <= N; i++)
        {
            H[i] = lower_bound(ord.begin(), ord.end(), H[i]) - ord.begin() + 1; 
        } 
        vector<vector<int>>adj(N + 2); 
        for(int i = 0; i < N; i++)
        {
            fenwick fenw;
            fenw.init(N + 3);   
            for(int j = i + 1; j <= N; j++)
            {
                if(H[i] < H[j])
                {
                    if(fenw.query(H[i] + 1, H[j] - 1) == 0)
                    {
                        adj[i].push_back(j); 
                    } 
                }
                fenw.upd(H[j], 1); 
            }
        }
        auto bfs = [&](int src)
        {
            queue<int>q; 
            q.push(src); 
            vector<int>dist(N + 2, -1);
            dist[src] = 0;  
            while(q.size())
            {
                int u = q.front();
                q.pop();
                for(auto v : adj[u])
                {
                    if(dist[v] == -1)
                    {
                        dist[v] = dist[u] + 1; 
                        q.push(v); 
                    }
                }
            }
            return dist[N]; 
        }; 
        int prefix = INT32_MAX;
        int src = N + 1;
        for(int i = 0; i < N; i++)
        {
            if(H[i] <= prefix)
            {
                adj[src].push_back(i); 
            }
            prefix = min(prefix, H[i]); 
        }
        cout << bfs(src) - 1 << '\n'; 
    }
    return 0;
}
// This is a shortest path problem edge (i, j) exist when there is no element k between i,j such that H[i] < H[k] < H[j]