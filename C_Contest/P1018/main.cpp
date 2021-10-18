//
//  main.cpp
//  P1018
//
//  Created by 蔡洪浩 on 2021/10/7.
//

#include <iostream>
using namespace std;
typedef long long ll;
const int N = 50;
int f[N][6];
char str[N];
int cal(int st,int en){
    ll sum = 0;
    for(int i = st ; i <= en ; i++){
        sum = sum * 10 + (str[i] -'0');
    }
    return sum;
}
int main(int argc, const char * argv[]) {
    int n,k; cin>>n>>k;
    cin>>str+1;
    for(int i = 1; i <= n; i++) f[i][0] = cal(1,i);
//    cout<<"-----"<<'\n';
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= k ; j++){
            for(int h = j; h <= i; h++){
                f[i][j] = max(f[h-1][j-1]*cal(h,i), f[i][j]);
            }
        }
    }
    cout<<f[n][k]<<'\n';
    return 0;
}
