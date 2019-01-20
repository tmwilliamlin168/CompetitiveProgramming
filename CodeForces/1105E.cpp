#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, m, qt, dp[1<<20];
map<string, int> mp;
vector<ll> v;
ll b[40];

int a() {
	string s;
	cin >> s;
	if(mp.find(s)==mp.end())
		mp.insert({s, mp.size()});
	return mp[s];
}

int cdp(ll i) {
	int ans=i<1<<20?dp[i]:0;
	if(!ans&&i) {
		int j=63-__builtin_clzll(i);
		ans=max(cdp(i^1ll<<j), cdp(i&b[j])+1);
	}
	if(i<1<<20)
		dp[i]=ans;
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> qt;
		if(qt==1)
			v.push_back(0);
		else
			v.back()|=1ll<<a();
	}
	for(ll vi : v)
		for(int i=0; i<m; ++i)
			for(int j=0; j<m; ++j)
				if(vi>>i&1&&vi>>j&1)
					b[i]|=1ll<<j;
	for(int i=0; i<m; ++i)
		b[i]=~b[i];
	cout << cdp((1ll<<m)-1);
}
