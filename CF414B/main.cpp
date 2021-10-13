//
//  main.cpp
//  CF414B
//
//  Created by 蔡洪浩 on 2021/10/13.
//


#include <iostream>
using namespace std;
const int N = 2e3+10;
int f[N][N];  // 处理到第n个数，这个数是k；
//f[i][j] += f[i-1][j/m]
const int mod = 1e9+7;

int main(int argc, const char * argv[]) {
    // insert code here...
    int n,k; cin>>n>>k;
    for(int i = 1; i <= n; i++) f[1][i] = 1;
    for(int i = 2; i <= k ; i++){
        for(int j = 1; j <= n ;j++){
            for(int m = j ; m <= n ;m += j){
                f[i][m] = (f[i][m] + f[i-1][j])%mod;
            }
        }
    }
    int sum = 0;
    for(int i = 1; i <= n; i++){
        sum = (sum + f[k][i]) %mod;
//        cout<<f[][
    }
    cout<<sum%mod<<'\n';
    return 0;
}
