#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int f[N][3], a[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < i; j++){
            if (a[i] > a[j])
                f[i][0] = max(f[i][0], f[j][0] + 1);
        }
    }
    for (int i = n; i >= 0; i--){
        for (int j = n+1 ; j > i; j--){
            if (a[i] > a[j])
                f[i][1] = max(f[i][1], f[j][1] + 1);
        }
    }
    int res = 0;
    for(int i = 1 ; i <= n ; i++){
        res = max(res, f[i][0] + f[i][1] -1 );
    }
    cout << n - res << '\n';
    return 0;
}