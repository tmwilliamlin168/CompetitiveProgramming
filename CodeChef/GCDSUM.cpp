#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=20, mxM=1e5, M=1e9+7;
int n, m, aij, a[mxN][mxM+1];
ll a1[mxM+1], a2;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> aij, ++a[i][aij];
	for(int i=mxM; i; --i) {
		a1[i]=1;
		for(int j=0; j<n; ++j) {
			int s=0;
			for(int k=i; k<=mxM; k+=i)
				s+=a[j][k];
			a1[i]=a1[i]*(s+1)%M;
			a2-=(long long)a[j][i]*i;
		}
		--a1[i];
		for(int j=2*i; j<=mxM; j+=i)
			a1[i]-=a1[j];
		a1[i]%=M;
		a2+=a1[i]*i%M;
	}
	cout << (a2%M+M)%M;
}
