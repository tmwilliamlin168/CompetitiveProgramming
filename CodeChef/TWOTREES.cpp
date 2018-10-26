#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int t, n[2], p[2][mxN], h[2][mxN];
vector<int> adj[2][mxN];
bool d[mxN];

void solve() {
	cin >> n[0] >> n[1];
	map<vector<int>, int> mp[2];
	for(int k=0; k<2; ++k) {
		for(int i=1; i<n[k]; ++i) {
			cin >> p[k][i], --p[k][i];
			adj[k][p[k][i]].push_back(i);
		}
		for(int i=n[k]-1; i>=0; --i) {
			vector<int> v;
			for(int j : adj[k][i])
				v.push_back(h[k][j]);
			sort(v.begin(), v.end());
			if(mp[k].find(v)==mp[k].end())
				mp[k].insert({v, mp[k].size()});
			h[k][i]=mp[k][v];
		}
	}
	int a1=0;
	memset(d, 0, n[0]);
	d[0]=1;
	for(int i=0; i<n[0]; ++i) {
		if(!d[i])
			continue;
		set<int> s;
		for(int j : adj[0][i])
			d[j]=s.insert(h[0][j]).second;
		a1+=!adj[0][i].size();
	}
	cout << (long long)a1*mp[1].size() << "\n";
	for(int k=0; k<2; ++k)
		for(int i=0; i<n[k]; ++i)
			adj[k][i].clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
