#include <bits/stdc++.h>
using namespace std;
 
const int mxN=18, M=998244353, I2=499122177;
int n, m, adj[mxN], ans, dp[1<<mxN];
vector<array<int, 2>> v[1<<mxN];
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0, a, b; i<m; ++i) {
		cin >> a >> b, --a, --b;
		adj[a]|=1<<b;
		adj[b]|=1<<a;
	}
	v[(1<<n)-1].push_back({(1<<n)-1, 1});
	for(int i=(1<<n)-1; ~i; --i) {
		for(array<int, 2> a : v[i]) {
			dp[a[0]]+=a[1];
			if(dp[a[0]]>=M)
				dp[a[0]]-=M;
			if(!i) {
				ans+=a[1];
				if(ans>=M)
					ans-=M;
			}
		}
		vector<array<int, 2>>().swap(v[i]);
		for(int j=i, k=n; ~j; j=j?(j-1)&i:-1) {
			if(!dp[j])
				continue;
			if(j) {
				while(j>>k&1^1)
					--k;
				v[i^1<<k].push_back({j^1<<k|adj[k]&i, dp[j]});
				dp[j^1<<k]+=dp[j];
				if(dp[j^1<<k]>=M)
					dp[j^1<<k]-=M;
			}
			dp[j]=0;
		}
	}
	cout << (long long)ans*m%M*I2%M;
}
