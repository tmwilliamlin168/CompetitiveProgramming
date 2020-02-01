#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, m, ew[mxN];

struct arborescence {
	static const int mxN=::mxN, mxM=::mxN;
	int p[mxN], vis[mxN], st[mxN], a[mxN-1], as, hp[mxN+mxM], g[mxN+mxM];
	ll d[mxN];
	set<array<ll, 4>> e[mxN];
	vector<int> f[mxN], hc[mxN+mxM];
	int find(int x) {
		return x^p[x]?(p[x]=find(p[x])):x;
	}
	ll solve(int n, int m, int s) {
		iota(p, p+n, 0);
		memset(d, 0, 8*n);
		memset(vis, -1, 4*n);
		ll ans=0;
		for(int i=0; i<n; ++i)
			f[i]={i};
		memset(hp, -1, 4*(n+m));
		iota(g, g+n, 0);
		memset(g+n, -1, 4*m);
		for(int i=0; i<n; ++i) {
			int sth=0;
			st[sth++]=i;
			while(find(st[sth-1])^s) {
				int u=st[sth-1];
				vis[u]=i;
				while(e[u].size()&&find((*e[u].begin())[1])==u)
					e[u].erase(e[u].begin());
				if(!e[u].size())
					return -1;
				int v=find((*e[u].begin())[1]);
				vector<int> nf;
				auto pr=[&](int x) {
					array<ll, 4> c=*e[x].begin();
					ll w=c[0]+d[x];
					ans+=w;
					d[x]-=w;
					for(int j : f[find(c[2])]) {
						hp[j]=n+c[3];
						hc[n+c[3]].push_back(j);
					}
					f[find(c[2])].clear();
					nf.push_back(n+c[3]);
					g[n+c[3]]=c[2];
				};
				if(v==s||vis[v]==i) {
					if(v^s)
						pr(v);
					--sth;
					do {
						pr(st[sth]);
						if(e[st[sth]].size()>e[v].size()) {
							swap(e[v], e[st[sth]]);
							swap(d[v], d[st[sth]]);
						}
						for(array<ll, 4> a : e[st[sth]])
							e[v].insert({a[0]+d[st[sth]]-d[v], a[1], a[2], a[3]});
						p[st[sth]]=v;
					} while(sth&&st[--sth]^v);
					f[v]=nf;
				}
				st[sth++]=v;
			}
		}
		return ans;
	}
	void dfs(int u, int n) {
		if(~g[u]) {
			a[as++]=u-n;
			for(int v=g[u]; ~v&&~g[v]; v=hp[v])
				g[v]=-1;
		}
		for(int v : hc[u])
			dfs(v, n);
		hc[u].clear();
	}
	void ca(int n, int m) {
		as=0;
		for(int i=0; i<m; ++i)
			if(hp[n+i]<0&&~g[n+i])
				dfs(n+i, n);
	}
} a;

int main() {
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	cin >> n >> m;
	for(int i=0, u, v; i<m; ++i) {
		cin >> u >> v >> ew[i], --u, --v;
		a.e[v].insert({ew[i], u, v, i});
	}
	ll ans=a.solve(n, m, 0);
	cout << ans << "\n";
	if(ans<0)
		return 0;
	a.ca(n, m);
	for(int i=0; i<n-1; ++i)
		if(ew[a.a[i]])
			cout << a.a[i]+1 << " ";
}
