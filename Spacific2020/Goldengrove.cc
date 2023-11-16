#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i];
        if(N == 1)
        {
            cout << 0 << '\n';
        }
        else 
        {
            sort(arr.begin(), arr.end()); 
            int ret = INT32_MAX; 
            for(int i = 0; i + 1 < N; i++) ret = min(ret, abs(arr[i + 1] - arr[i])); 
            cout << ret << '\n'; 
        }
    }
    return 0; 
}