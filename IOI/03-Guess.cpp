#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

int n, p, m[50];
char c[50][8];
ll o[8][7];
vector<ar<int, 2>> u;
vector<ll> v;
vector<ar<int, 3>> dp;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> p;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<p; ++j) {
			cin >> c[i][j];
			c[i][j]-='X';
			m[i]|=1<<j*3+c[i][j];
			for(int k=1; k<7; ++k)
				if(k>>c[i][j]&1)
					o[j][k]|=1ll<<i;
		}
		for(int j=m[i]; j<1<<3*p; j=j+1|m[i])
			u.push_back({j, i});
	}
	sort(u.begin(), u.end());
	for(int i=0, j=0; i<u.size();) {
		for(; j<u.size()&&u[j][0]==u[i][0]; ++j);
		v.push_back(0);
		for(; i<j; ++i)
			v.back()|=1ll<<u[i][1];
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end())-v.begin());
	auto gi=[](ll x) {
		return lower_bound(v.begin(), v.end(), x)-v.begin();
	};
	for(int i=0; i<v.size(); ++i) {
		dp.push_back({2*p+1});
		if(__builtin_popcountll(v[i])>1) {
			for(int j=0; j<p; ++j) {
				for(int k=1; k<4; ++k) {
					ll v1=v[i]&o[j][k], v2=v[i]^v1;
					if(v1&&v2)
						dp[i]=min(ar<int, 3>{max(dp[gi(v1)][0], dp[gi(v2)][0])+1, j, k}, dp[i]);
				}
			}
		} else
			dp[i]={};
	}
	int u=v.size()-1, a;
	while(dp[u][0]) {
		cout << "Q " << dp[u][1]+1;
		for(int i=0; i<3; ++i)
			if(dp[u][2]>>i&1)
				cout << " " << char('X'+i);
		cout << endl;
		cin >> a;
		u=gi(v[u]&o[dp[u][1]][dp[u][2]^(a?0:7)]);
	}
	cout << "C " << __builtin_ctzll(v[u])+1;
}
