//
//  main.cpp
//  P1057
//
//  Created by 蔡洪浩 on 2021/10/8.
//

#include <iostream>
using namespace std;
const int N = 55;
int f[N][N];
int main(int argc, const char * argv[]) {
    int n,m; cin>>n>>m;
    f[1][0] = 1;
    for(int j = 1; j <= m; j++){
        for(int i = 1; i <= n; i++){
            if(i == 1) f[i][j] = f[n][j-1] + f[2][j-1];
            else if(i == n) f[i][j] = f[n-1][j-1] + f[1][j-1];
            else f[i][j] = f[i-1][j-1] + f[i+1][j-1];
    //            cout<<f[i][j]<<endl;
        }
    }
    cout<<f[1][m]<<'\n';
    return 0;
}
