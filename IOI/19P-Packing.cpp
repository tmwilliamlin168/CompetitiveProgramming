#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, k, a[mxN], l, p[mxN];
vector<int> v[11], u(11);
vector<vector<int>> g[21];

void dfs(int s, int i) {
	g[s].push_back(u);
	for(int j=min(10, 20-s); j>=i; --j) {
		++u[j];
		dfs(s+j, j);
		--u[j];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		v[a[i]].push_back(i);
	}
	dfs(0, 1);
	while(v[7].size()>4696&&v[5].size()>4696) {
		p[v[7].back()]=l;
		v[7].pop_back();
		p[v[7].back()]=l;
		v[7].pop_back();
		p[v[5].back()]=l;
		v[5].pop_back();
		++l;
	}
	for(int bc=20; bc; ) {
		vector<int> bw;
		ll bwc=1e18;
		for(vector<int> &w : g[bc]) {
			bool ok=1;
			ll hc=0;
			for(int i=1; i<=10&&ok; ++i) {
				ok=v[i].size()>=w[i];
				hc+=(ll)i*i*(v[i].size()-w[i])*(v[i].size()-w[i]);
			}
			if(ok&&hc<bwc) {
				bw=w;
				bwc=hc;
			}
		}
		if(bwc>=1e18) {
			--bc;
			continue;
		}
		for(int i=1; i<=10; ++i) {
			for(int j=0; j<bw[i]; ++j) {
				p[v[i].back()]=l;
				v[i].pop_back();
			}
		}
		++l;
	}
	cout << l << "\n";
	for(int i=0; i<n; ++i)
		cout << p[i] << " ";
}
