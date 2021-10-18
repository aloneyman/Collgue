//
//  main.cpp
//  dp
//
//  Created by 蔡洪浩 on 2021/10/6.
//

#include<iostream>
using namespace std;
int m,n;
int f[20010];
int w[40];
int main(){
//    cout<<"------"<<endl;
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=w[i];j--){
            if(f[j]<f[j-w[i]]+w[i]){
                f[j]=f[j-w[i]]+w[i];
            }
        }
    }
    cout<<m-f[m]<<endl;
    getchar();
}
