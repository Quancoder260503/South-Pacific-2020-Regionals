#include "bits/stdc++.h"
using namespace std;
#define START 10
const int M = 10000;
signed main(void)
{
    int T, P, C;
    while (cin >> T >> P >> C)
    {
        vector<set<int>>board(M);
        vector<vector<int>>prob(C);
        vector<int>exp(C);
        vector<int>tprob(P);  
        vector<string>type(C); 
        for(int i = 0; i < P; i++) cin >> tprob[i]; 
        vector<vector<int>>ret(C, vector<int>(P)); 
        vector<vector<int>>vis(C, vector<int>(P)); 
        vector<vector<int>>nvis(C, vector<int>(M)); 
        for(int i = 0; i < C; i++) 
        {
            cin >> type[i] >> exp[i]; 
            for(int j = 0; j < P; j++)
            {
                int x; 
                cin >> x; 
                --x; 
                prob[i].push_back(x); 
            }
            if(type[i] == "maa")
            {
                int curr = START; 
                for(int j = 0; j < P; j++)
                {
                    curr += tprob[prob[i][j]] * exp[i]; 
                    if(curr >= T) break; 
                    board[curr + 1].insert(prob[i][j]); 
                    ret[i][prob[i][j]] = curr; 
                }
            }
        }
        for(int at = START; at <= T; at++)
        {
            for(auto it : board[at - 1])
            {
                board[at].insert(it); 
            }
            for(int i = 0; i < C; i++)
            {
                nvis[i][at] += nvis[i][at - 1]; 
                if(type[i] == "maa") continue; 
                for(int j = 0; j < prob[i].size(); j++)
                {
                    if(!nvis[i][at] && board[at].count(prob[i][j]) && !vis[i][prob[i][j]])
                    {
                        vis[i][prob[i][j]] = 1; 
                        ret[i][prob[i][j]] = at + exp[i] * tprob[prob[i][j]]; 
                        nvis[i][at + 1]++;
                        nvis[i][at + exp[i] * tprob[prob[i][j]]]--;  
                        break; 
                    }
                }
            }
        }
        for(int i = 0; i < C; i++)
        {
            for(int j = 0; j < P; j++)
            {
                cout << (ret[i][j] < T ? ret[i][j] : 0) << " "; 
            }
            cout << '\n'; 
        }
    } 
    return 0;
}