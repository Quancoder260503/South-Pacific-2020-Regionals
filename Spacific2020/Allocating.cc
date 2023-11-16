#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int64_t N; 
    while(cin >> N)
    {
        int64_t M = N; 
        N = floor(sqrt(N)); 
        int64_t ret = 0;
        for(int i = 1; i <= N; i++)
        {
            ret += M / i; 
        }
        ret = 2 * ret - N * N;
        cout << ret << '\n';  
    }
    return 0; 
}