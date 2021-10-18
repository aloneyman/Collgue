//
//  main.cpp
//  P1077
//
//  Created by 蔡洪浩 on 2021/10/16.
//

#include <iostream>
using namespace std;
const int mod = 1e6+7;
const int N = 1e3+10;
int f[N][N],a[N];
int main(int argc, const char * argv[]) {
    int n,m; cin>>n>>m;
    for(int i = 1; i <= n ;i++){
        cin >> a[i];
    }
    f[0][0] = 1;
    
    for(int i = 1 ; i <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= min(j,a[i]); k++){
                f[i][j] = (f[i][j] + f[i-1][j-k])%mod;
            }
        }
    }
    cout<<f[n][m]<<'\n';
    return 0;
}
