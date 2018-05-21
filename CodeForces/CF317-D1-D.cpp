/*
	- If x is not the power of any number, then x, x^2, x^3, ... can form their own subgame
	- Find the grundy numbers of all subgames to solve the problem
	- Since 2^30 > 10^9, there can only be 29 numbers in a subgame
	- Precalculate the subgames with dp
		- Using char instead of int can save memory (2GB => 0.5GB)
		- Using memoization can save a lot of time
*/

#include <bits/stdc++.h>
using namespace std;

/*
char dp[1<<29];

char cdp(int m) {
	if(dp[m]==69) {
		vector<int> pg;
		for(int i=0; i<29; ++i) {
			if(!(m>>i&1))
				continue;
			int ni=m;
			for(int j=i; j<29; j+=i+1)
				ni&=~(1<<j);
			pg.push_back(cdp(ni));
		}
		sort(pg.begin(), pg.end());
		pg.push_back(69);
		if(!pg[0]) {
			for(int i=0; dp[m]==69; ++i)
				if(pg[i]+1<pg[i+1])
					dp[m]=pg[i]+1;
		} else
			dp[m]=0;
	}
	return dp[m];
}

inline void precalc() {
	memset(dp, 69, sizeof(dp));
	for(int i=1; i<=29; ++i)
		cout << cdp((1<<i)-1)+0 << ", ";
}
//*/

int n, n2, x, gv[]={1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12};
unordered_set<int> isp;

inline void solve() {
	cin >> n, n2=n;
	for(int i=2; i*i<=n; ++i) {
		if(isp.find(i)!=isp.end())
			continue;
		int na=-1;
		for(long long j=i; j<=n; j*=i, ++na, --n2)
			isp.insert(j);
		x^=gv[na];
	}
	x^=n2&1;
	cout << (x?"Vasya":"Petya");
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
//	precalc();
	solve();
}
