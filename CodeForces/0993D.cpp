/*
	- Sort tasks in decreasing power and then by decreasing number of processors
	- Optimize fraction with binary search
	- Check if a/b<=c, same as a-c*b<=0
	- dp[i][j] = minimum value of sum of a-c*b with first i tasks and there are j more "first" tasks
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second

const int mxN=50;
const ll INF=1e18;
int n;
pll ps[mxN+1];
ll dp[mxN+1][mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> ps[i].fi;
	for(int i=0; i<n; ++i)
		cin >> ps[i].se;
	sort(ps, ps+n, greater<pll>());
	ll lb=1, rb=1e12;
	while(lb<=rb) {
		ll mb=(lb+rb)/2;
		dp[0][0]=0;
		for(int i=1; i<=n; ++i)
			dp[0][i]=INF;
		for(int i=1; i<=n; ++i) {
			int k=i;
			while(k<n&&ps[k].fi==ps[k-1].fi)
				++k;
			ll cs=0;
			for(int j=0; j<=n; ++j)
				dp[k][j]=INF;
			for(int l=0; l<=k-i+1; ++l) {
				for(int j=l; j+(k-i+1)-2*l<=n&&j<=n; ++j)
					dp[k][j]=min(dp[i-1][j+(k-i+1)-2*l]+cs, dp[k][j]);
				cs+=1000*ps[i-1+l].fi-mb*ps[i-1+l].se;
			}
			i=k;
		}
		bool ok=0;
		for(int i=0; i<=n&&!ok; ++i)
			ok=dp[n][i]<=0;
		if(ok)
			rb=mb-1;
		else
			lb=mb+1;
	}
	cout << lb;
}
