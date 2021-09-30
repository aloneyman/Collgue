//
//  NNT.cpp
//  Demo
//
//  Created by 蔡洪浩 on 2021/9/30.
//

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double Pi = acos(-1.0);
int n,m,rev[2100005];

struct complex{
    double x,y;
    inline complex operator + (const complex &a) const{return complex{x + a.x,y + a.y};}
    inline complex operator - (const complex &a) const{return complex{x - a.x,y - a.y};}
    inline complex operator * (const complex &a) const{return complex{x * a.x - y * a.y,x * a.y + y * a.x};}
}a[2100005],b[2100005];
void FFT(complex *a,int lent,int inv)
{
    if (lent == 1) return;
    for (int i = 0; i < lent; ++i)
        if (i < rev[i]) swap(a[i],a[rev[i]]);
    for (int l = 1; l < lent; l <<= 1)
    {
        complex I = complex{cos(Pi / l),inv * sin(Pi / l)};
        for (int i = 0; i < lent; i += (l << 1))
        {
            complex w = complex{1,0};
            for (int j = 0; j < l; ++j,w = w * I)
            {
                complex x = a[i + j],y = w * a[i + j + l];
                a[i + j] = x + y,a[i + j + l] = x - y;
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i = 0; i <= n; ++i) scanf("%lf",&a[i].x);
    for (int i = 0; i <= m; ++i) scanf("%lf",&b[i].x);
    int len = 1,bit = 0;
    while (len <= n + m) len <<= 1,++bit;
    for (int i = 0; i < len; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    FFT(a,len,1),FFT(b,len,1);
    for (int i = 0; i < len; ++i) a[i] = a[i] * b[i];
    FFT(a,len,-1);
    for (int i = 0; i <= n + m; ++i) printf("%d ",(int)(a[i].x / len + 0.5));
}
