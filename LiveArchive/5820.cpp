#include <bits/stdc++.h>
using namespace std;

const int mxM=600, mxN=2*mxM;
int m, ai, n, r[mxN], qu[mxM], p[mxM];
unordered_map<int, int> mp;
array<int, 2> a[mxM];
vector<int> adj2[mxN];
bool is[mxM], adj[mxM][mxM], vis[mxN];

int ri() {
	cin >> ai;
	if(mp.find(ai)==mp.end())
		mp.insert({ai, mp.size()});
	return mp[ai];
}

void dfs(int u, int ru) {
	r[u]=ru;
	vis[u]=1;
	for(int v : adj2[u])
		if(!vis[v])
			dfs(v, ru);
}

void solve() {
	for(int i=0; i<m; ++i)
		a[i]={ri(), ri()};
	n=mp.size();
	memset(is, 0, m);
	int ans=0;
	for(int i=0; i<n; ++i)
		adj2[i].clear();
	vector<int> tu(n);
	iota(tu.begin(), tu.end(), 0);
	auto fr=[&]() {
		memset(vis, 0, n);
		for(int i : tu)
			if(!vis[i])
				dfs(i, i);
		tu.clear();
	};
	auto tg=[&](int i) {
		for(int j : {0, 1}) {
			if(is[i])
				adj2[a[i][j]].erase(find(adj2[a[i][j]].begin(), adj2[a[i][j]].end(), a[i][j^1]));
			else
				adj2[a[i][j]].push_back(a[i][j^1]);
			tu.push_back(a[i][j]);
		}
		is[i]^=1;
	};
	for(int i=0; i<m; ++i) {
		fr();
		if(!is[i^1]&&r[a[i][0]]!=r[a[i][1]]) {
			tg(i);
			++ans;
		}
	}
	while(1) {
		memset(adj, 0, sizeof(adj));
		for(int i=0; i<m; ++i) {
			if(!is[i])
				continue;
			tg(i);
			fr();
			for(int j=0; j<m; ++j) {
				adj[i][j]=!is[j]&&r[a[j][0]]!=r[a[j][1]];
				adj[j][i]=!is[j]&&!is[j^1];
			}
			tg(i);
		}
		fr();
		memset(p, -1, 4*m);
		int qt=0, ee=-1;
		for(int i=0; i<m; ++i) {
			if(!is[i]&&r[a[i][0]]!=r[a[i][1]]) {
				qu[qt++]=i;
				p[i]=-2;
			}
		}
		for(int qh=0; qh<qt&&ee==-1; ) {
			int u=qu[qh++];
			if(!is[u]&&!is[u^1])
				ee=u;
			for(int v=0; v<m; ++v) {
				if(adj[u][v]&&p[v]==-1) {
					p[v]=u;
					qu[qt++]=v;
				}
			}
		}
		if(ee==-1)
			break;
		for(; ee!=-2; ee=p[ee])
			tg(ee);
		++ans;
	}
	cout << ans*2 << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	while(1) {
		cin >> m, m*=2;
		if(!m)
			break;
		solve();
		mp.clear();
	}
}
