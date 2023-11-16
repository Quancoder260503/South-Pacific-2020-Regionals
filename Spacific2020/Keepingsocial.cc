#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        auto dist = [&](pair<int, int>a, pair<int, int>b)
        {
            return 1LL * (a.first - b.first) * (a.first - b.first) + 1LL * (a.second - b.second) * (a.second - b.second); 
        }; 
        vector<pair<int,int>>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i].first >> arr[i].second; 
        int64_t ret = 0; 
        vector<pair<int, int>>pidx;
        for(int i = 0; i < N; i++) for(int j = i + 1; j < N; j++)
        {
            pidx.push_back({i, j}); 
        } 
        auto cmp = [&](pair<int, int>a, pair<int, int>b)
        {
            return dist(arr[a.first], arr[a.second]) < dist(arr[b.first], arr[b.second]); 
        }; 
        sort(pidx.begin(), pidx.end(), cmp); 
        vector<int>vis(N); 
        for(auto [u, v] : pidx)
        {
            if(vis[u] || vis[v])
            {
                cout << dist(arr[u], arr[v]) << '\n'; 
                goto done; 
            }
            vis[u] = vis[v] = 1; 
        }
    done: 
        continue; 
    }
    return 0; 
}