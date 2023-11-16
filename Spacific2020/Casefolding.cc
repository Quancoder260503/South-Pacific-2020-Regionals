#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N, M, K; 
    while(cin >> N >> M >> K)
    {
        vector<vector<int>>G(N, vector<int>(M)); 
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                char x; 
                cin >> x; 
                G[i][j] = (x == 'x'); 
            }
        }
        vector<vector<char>>ret(N, vector<char>(K)); 
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; K - j - 1 >= 0 && K + j < M; j++)
            {
                ret[i][K - j - 1] = G[i][K - j - 1] | G[i][K + j];  
            }
            if(K < M - K)
            {
                reverse(ret[i].begin(), ret[i].end()); 
                for(int j = 2 * K; j < M; j++) ret[i].push_back(G[i][j]);
                reverse(ret[i].begin(), ret[i].end()); 
            }
            else 
            {
                for(int j = 2 * K - M - 1; j >= 0; j--) ret[i][j] = G[i][j]; 
            }
        }
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < ret[i].size(); j++)
            {
                cout << (ret[i][j] ? 'x' : 'o'); 
            }
            cout << '\n'; 
        }
    }
    return 0; 
}