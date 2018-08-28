/*
	- http://codeforces.com/blog/entry/60982/#comment-454544
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=5e5, M=1e9+7;
int n, a[mxN], l[mxN], r[mxN], b1[mxN+1], b2[mxN+1], qu[mxN], qh, qt;
ll dp[mxN+3];
vector<pii> t1[mxN+2], t2[mxN+2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		l[i]=i-1;
		while(l[i]>=0&&a[l[i]]<a[i])
			l[i]=l[l[i]];
	}
	for(int i=n-1; i>=0; --i) {
		r[i]=i+1;
		while(r[i]<n&&a[r[i]]<=a[i])
			r[i]=r[r[i]];
		if(i-l[i]<r[i]-i)
			for(int j=l[i]; j<i; ++j)
				t1[j+2].push_back({i+2, min(r[i]+2, j+3+a[i])});
		else
			for(int j=i; j<r[i]; ++j)
				t2[j+2].push_back({max(l[i]+1, j+1-a[i]), i+1});
	}
	for(int i1=0, i2=0; i1<n; ++i1) {
		while(qh<qt&&a[qu[qt-1]]>=a[i1])
			--qt;
		qu[qt++]=i1;
		while(i2<=i1&&i1-i2+1>=a[qu[qh]]) {
			if(qu[qh]==i2)
				++qh;
			++i2;
		}
		b1[i1+1]=i2;
	}
	for(int i=1; i<=n; ++i)
		b2[b1[i]]=i;
	for(int i=1; i<=n; ++i)
		b2[i]=max(b2[i-1], b2[i]);
	dp[1]=1;
	dp[2]=-1;
	for(int i=1; i<=n+1; ++i) {
		dp[i+1]+=dp[i];
		for(pii p : t2[i])
			if(p.fi<min(p.se, b1[i-1]))
				dp[i]+=dp[min(p.se, b1[i-1])]-dp[p.fi]+M;
		dp[i]%=M;
		for(pii p : t1[i]) {
			if(max(p.fi, b2[i-1]+2)<p.se) {
				dp[max(p.fi, b2[i-1]+2)]+=dp[i];
				dp[p.se]+=M-dp[i];
			}
		}
		dp[i]=(dp[i-1]+dp[i])%M;
	}
	cout << (dp[n+1]-dp[n]+M)%M;
}
