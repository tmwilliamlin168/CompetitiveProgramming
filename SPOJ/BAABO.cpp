/*
	- If we use a[i] and b[j], then we also use at least one of a[i-1] or b[j-1]
	- Thus, dp[i][j] only transitions from dp[i-1][k] or dp[k][j-1] and we can use CHT for fast transitions
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e3;
int n;
ll a[mxN+2], b[mxN+2], dp[2][mxN+2];

struct cht {
	ll a[mxN+2], b[mxN+2];
	int qh, qt;
	void upd(ll c, ll d) {
		if(qt&&c==a[qt-1]) {
			if(d<b[qt-1])
				return;
			--qt;
		}
		while(qt-qh>1&&(a[qt-2]-c)*(b[qt-1]-b[qt-2])>(a[qt-2]-a[qt-1])*(d-b[qt-2]))
			--qt;
		a[qt]=c;
		b[qt]=d;
		++qt;
	}
	ll qry(ll c) {
		while(qt-qh>1&&a[qh]*c+b[qh]<a[qh+1]*c+b[qh+1])
			++qh;
		return qt>qh?a[qh]*c+b[qh]:-1e12;
	}
} rc[2], cc[mxN+2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> a[i], a[i]+=a[i-1];
	for(int i=1; i<=n; ++i)
		cin >> b[i], b[i]+=b[i-1];
	a[n+1]=a[n];
	b[n+1]=b[n];
	rc[0].upd(0, 0);
	cc[0].upd(0, 0);	
	for(int i=1; i<=n+1; ++i) {
		if(i>1)
			rc[i&1^1].qh=rc[i&1^1].qt=0;
		for(int j=1; j<=n+1; ++j) {
			if(i>1)
				cc[j].upd(2*a[i-1], dp[i&1^1][j]-a[i-1]*a[i-1]);
			dp[i&1][j]=(a[i]-a[i-1])*(b[j]-b[j-1])+max(rc[i&1^1].qry(b[j-1])-b[j-1]*b[j-1], cc[j-1].qry(a[i-1])-a[i-1]*a[i-1]);
			if(i>1)
				rc[i&1^1].upd(2*b[j], dp[i&1^1][j]-b[j]*b[j]);
		}
		if(i==n+1)
			cout << dp[i&1][n+1];
	}
}
