#include<iostream>
using namespace std;
int m,n;
int f[20010];
int w[40];
int main(){
	cin>>n>>m;
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
}


