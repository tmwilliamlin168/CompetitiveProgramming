#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define se second

const int mxN=1e5;
int t, n, a[mxN], b[mxN], d[mxN], p[mxN];
ll s;
unordered_map<int, int> mp;
vector<int> adj[mxN];
pii st[2*mxN];
bool vis[mxN];

inline void upd(int i, pii x) {
	for(i+=n; i; i/=2)
		st[i]=max(x, st[i]);
}

inline pii qry(int l, int r) {
	pii p={0, -1};
	for(l=max(l, 0)+n, r=min(r, n)+n; l<r; ++l/=2, r/=2) {
		if(l&1)
			p=max(st[l], p);
		if(r&1)
			p=max(st[r-1], p);
	}
	return p;
}

void dfs(int u) {
	vis[u]=1;
	for(int v : adj[u]) {
		if(!vis[v])
			dfs(v);
		d[u]=max(d[v]+1, d[u]);
	}
}

inline ll chk(int k) {
	mp.clear();
	for(int i=0; i<n; ++i)
		mp[a[i]]=-k-1;
	for(int i=0; i<n; ++i) {
		b[i]=mp[a[i]]+k<i?i:b[mp[a[i]]];
		mp[a[i]]=i;
	}
	for(int i=0; i<n; ++i)
		adj[i].clear();
	for(int i=1; i<2*n; ++i)
		st[i]={0, -1};
	for(int i1=0; i1<n; ) {
		int i2=i1;
		while(i2+1<n&&a[p[i2+1]]==a[p[i1]])
			++i2;
		for(int j=i1; j<=i2; ++j) {
			pii p1=qry(p[j]-k, p[j]), p2=qry(p[j]+1, p[j]+k+1);
			if(p1.se!=-1)
				adj[b[p[j]]].push_back(p1.se);
			if(p2.se!=-1)
				adj[b[p[j]]].push_back(p2.se);
		}
		for(int j=i1; j<=i2; ++j)
			upd(p[j], {a[p[j]], b[p[j]]});
		i1=i2+1;
	}
	ll cs=0;
	memset(vis, 0, n);
	memset(d, 0, 4*n);
	for(int i=0; i<n; ++i) {
		if(b[i]==i&&!vis[i])
			dfs(i);
		cs+=d[b[i]]+1;
	}
	return cs;
}
 
inline void solve() {
	cin >> n >> s;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		p[i]=i;
	}
	sort(p, p+n, [&](const int &i, const int &j) {
		return a[i]<a[j];
	});
	int lb=0, rb=n;
	while(lb<=rb) {
		int mb=(lb+rb)/2;
		if(chk(mb)<=s)
			lb=mb+1;
		else
			rb=mb-1;
	}
	cout << rb+1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
