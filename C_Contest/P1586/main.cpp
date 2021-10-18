//
//  main.cpp
//  P1586
//
//  Created by 蔡洪浩 on 2021/10/17.
//
#include <cmath>
#include <iostream>
using namespace std;
const int N = 33000;
int f[N][5]={0};
int main(int argc, const char * argv[]) {
    int t; cin>>t;
    f[0][0] = 1;
    for(int i = 1; i*i <=32768; i++){
        for(int k = i*i; k <= 32768; k++){
            for(int j = 1; j <= 4; j++){
                f[k][j] += f[k-i*i][j-1];
            }
        }
    }
    while(t--){
        int n; cin>>n;
        int res = 0;
        for(int i = 1; i <= 4 ;i++){
            res += f[n][i];
        }
        cout<< res <<'\n';
    }
    
    return 0;
}
