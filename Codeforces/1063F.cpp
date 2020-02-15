#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5e5, B=69;
int n, dp[mxN], ans;
ll pB[mxN+1], ps[mxN+1];
string s;
unordered_set<ll> us;

ll qry(int l, int r) {
	return ps[r+1]-ps[l]*pB[r-l+1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> s;
	pB[0]=1;
	for(int i=0; i<n; ++i) {
		ps[i+1]=ps[i]*B+s[i]-'a'+1;
		pB[i+1]=pB[i]*B;
	}
	for(int i=n-1; i>=0; ans=max(dp[i], ans), --i) {
		dp[i]=i<n-1?dp[i+1]+1:1;
		while(dp[i]>1&&us.find(qry(i, i+dp[i]-2))==us.end()&&us.find(qry(i+1, i+dp[i]-1))==us.end()) {
			--dp[i];
			for(int j=dp[i+dp[i]]; j&&us.insert(qry(i+dp[i], i+dp[i]+j-1)).second; --j);
		}
	}
	cout << ans;
}
