/*
	- Go through edges from lowest to highest weight
	- Consider each group of edges with the same weight
		- Number of paths with that edge as the edge with maximum weight can be calculated with dfs on the compressed graph
		- Connect the edges after calculating the answers for those edges
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int n, a[mxN], b[mxN], p[mxN], s[mxN], d;
ll a1[mxN+1], s2[mxN], a2;
bool vis[mxN];
vector<int> adj[mxN], a3, cn;
pii ps[mxN-1];

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

inline void join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return;
	if(s[x]<s[y])
		p[x]=y;
	else
		p[y]=x;
	s[x]=s[y]=s[x]+s[y];
}

void dfs1(int u) {
	vis[u]=1;
	for(int e : adj[u]) {
		int v=u^a[e]^b[e];
		if(vis[v])
			continue;
		dfs1(v);
		s2[u]+=s2[v];
	}
}

void dfs2(int u, int p, int ps) {
	a1[p]=s2[u]*ps;
	for(int e : adj[u]) {
		if(e==p)
			continue;
		int v=u^a[e]^b[e];
		dfs2(v, e, ps+s2[u]-s2[v]);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n-1; ++i) {
		cin >> a[i] >> b[i] >> d, --a[i], --b[i];
		ps[i]={d, i};
	}
	sort(ps, ps+n-1);
	for(int i=0; i<n; ++i)
		p[i]=i, s[i]=1;
	for(int i=0; i<n-1; ++i) {
		int j=i--;
		while(i+1<n&&ps[i+1].fi==ps[j].fi) {
			++i;
			a[ps[i].se]=find(a[ps[i].se]);
			b[ps[i].se]=find(b[ps[i].se]);
			adj[a[ps[i].se]].push_back(ps[i].se);
			adj[b[ps[i].se]].push_back(ps[i].se);
			cn.push_back(a[ps[i].se]);
			cn.push_back(b[ps[i].se]);
		}
		for(int u : cn)
			s2[u]=s[u];
		for(int u : cn) {
			if(!vis[u]) {
				dfs1(u);
				dfs2(u, n, 0);
			}
		}
		for(int u : cn)
			vis[u]=0;
		for(int k=j; k<=i; ++k) {
			adj[a[ps[k].se]].clear();
			adj[b[ps[k].se]].clear();
			join(a[ps[k].se], b[ps[k].se]);
		}
		cn.clear();
	}
	for(int i=0; i<n-1; ++i) {
		if(a1[i]>a2) {
			a2=a1[i];
			a3.clear();
		}
		if(a1[i]==a2)
			a3.push_back(i);
	}
	cout << a2*2 << " " << a3.size() << "\n";
	for(int ai : a3)
		cout << ai+1 << " ";
}
