#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int t, n, p, s[mxN], dp[mxN], ans[17][mxN];
vector<pii> ps;

inline int lg2(int x) {
	return 31-__builtin_clz(x);
}

inline void solve() {
	cin >> n >> p;
	for(int i=0; i<n; ++i)
		cin >> s[i];
	if(n<=1) {
		cout << (s[0]>=p);
		return;
	}
	sort(s, s+n);
	p-=s[n-1];
	if(p<=0) {
		for(int i=0; i<n; ++i)
			cout << n << " ";
		return;
	}
	int a1=0, p2=p;
	while(p2>0) {
		++a1;
		if(a1>=n)
			break;
		p2-=s[n-1-a1];
	}
	ps.clear();
	for(int i=n-2, s2=-s[n-2]; i>=0&&s2<2*p; s2+=s[i--]) {
		if(ps.empty()||ps.back().fi!=s[i])
			ps.push_back({s[i], 0});
		++ps.back().se;
	}
	for(int i=0; i<=lg2(n); ++i)
		memset(ans[i], 0, 4*(n+1-(1<<i)));
	memset(dp, 0x3F, 4*p);
	dp[0]=0;
	for(int i=0, s1=0, s2=0; i<ps.size(); s1+=ps[i].se, s2+=ps[i].fi*ps[i].se, ++i) {
		for(int j=max(p-ps[i].fi*ps[i].se, 0); j<min(s2+1, p); ++j) {
			if(dp[j]>p)
				continue;
			int a=(p-j-1)/ps[i].fi+1, b=(max(p-(s2-j), 0)+ps[i].fi-1)/ps[i].fi, l=dp[j]+a, r=dp[j]+n-1-s1-b, k=lg2(r-l+1);
			if(a+b>ps[i].se||l>r)
				continue;
			ans[k][l]=max(n+1-s1-a-b, ans[k][l]);
			ans[k][r-(1<<k)+1]=max(n+1-s1-a-b, ans[k][r-(1<<k)+1]);
		}
		for(int j=0, c=ps[i].se; c; ++j) {
			int x=min(1<<j, c);
			for(int j=p-x*ps[i].fi-1; j>=0; --j)
				dp[j+x*ps[i].fi]=min(dp[j]+x, dp[j+x*ps[i].fi]);
			c-=x;
		}
	}
	for(int i=lg2(n); i; --i) {
		for(int j=0; j<=n-(1<<i); ++j) {
			ans[i-1][j]=max(ans[i][j], ans[i-1][j]);
			ans[i-1][j+(1<<(i-1))]=max(ans[i][j], ans[i-1][j+(1<<(i-1))]);
		}
	}
	for(int i=0; i<n; ++i)
		cout << max(ans[0][i], max(n-i, i+1)-a1) << " ";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--) {
		solve();
		cout << "\n";
	}
}
