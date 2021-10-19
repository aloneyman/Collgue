#include<bits/stdc++.h>
using namespace std;
const int N = 1e2+10;
int a[N],f[N][N];
int fun(int l,int r){
    return abs(a[l]-a[r])*(abs(r-l+1));
}
int main() {
    int n; cin>>n;
    for(int i = 1 ; i <= n; i++) cin>>a[i],f[i][i]=a[i];
    for(int len = 2; len <= n; len++){
        for(int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            for(int k = l ; k <= r; k++){
                f[l][r] = max(f[l][r] , f[k+1][r] + fun(l,k));
            }
            for(int k = l; k <= r; k++){
                f[l][r] = max(f[l][r] , f[l][k] + fun(k+1,r));
            }
        }
    }
    cout << f[1][n] << '\n';
    return 0;
}