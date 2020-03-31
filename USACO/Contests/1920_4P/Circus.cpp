#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e5, M=1e9+7;
int n, dt, ds[mxN], td[mxN], k, md1[mxN], md2[mxN], d[mxN], anc[mxN][17], a2[mxN], s[mxN], p[mxN];
vector<int> adj[mxN], adj2[mxN];
ll iv[mxN+1], f1[mxN+1], f2[mxN+1], ans=1;
bool vis[mxN];
vector<ar<int, 2>> ta[1<<18], st;

int find(int x) {
	return x^p[x]?find(p[x]):x;
}

void join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return;
	if(s[x]>s[y])
		swap(x, y);
	st.push_back({x, y});
	p[x]=y;
	ans=ans*f1[s[x]]%M*f1[s[y]]%M;
	s[y]+=s[x];
	ans=ans*f2[s[y]]%M;
}

void dfs1(int u=0, int p=-1) {
	md1[u]=adj[u].size()>2?d[u]:(int)1e9;
	if(~p)
		adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
	anc[u][0]=p;
	for(int i=1; i<17; ++i)
		anc[u][i]=~anc[u][i-1]?anc[anc[u][i-1]][i-1]:-1;
	for(int v : adj[u]) {
		d[v]=d[u]+1;
		dfs1(v, u);
		md1[u]=min(md1[u], md1[v]);
	}
	td[ds[u]=dt++]=u;
}

void dfs3(int u=0, int pd=1e9) {
	md2[u]=pd;
	if(!u&&adj[u].size()<3) {
		if(adj[u].size()>1) {
			dfs3(adj[u][0], md1[adj[u][1]]+1);
			dfs3(adj[u][1], md1[adj[u][0]]+1);
		} else
			dfs3(adj[u][0], pd);
	} else
		for(int v : adj[u])
			dfs3(v, adj[u].size()>1?1:pd+1);
}

int dfs2(int u) {
	int s=1;
	vis[u]=1;
	for(int v : adj2[u])
		if(!vis[v])
			s+=dfs2(v);
	return s;
}

int lca(int u, int v) {
	if(d[u]<d[v])
		swap(u, v);
	for(int i=16; ~i; --i)
		if(d[u]-(1<<i)>=d[v])
			u=anc[u][i];
	if(u==v)
		return u;
	for(int i=16; ~i; --i)
		if(anc[u][i]^anc[v][i])
			u=anc[u][i], v=anc[v][i];
	return anc[u][0];
}

void ae(int l1, int r1, ar<int, 2> e, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		ta[i].push_back(e);
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		ae(l1, r1, e, 2*i, l2, m2);
	if(m2<r1)
		ae(l1, r1, e, 2*i+1, m2+1, r2);
}

void dc(int i=1, int l2=0, int r2=n-1) {
	int sts=st.size();
	for(ar<int, 2> e : ta[i])
		join(e[0], e[1]);
	if(l2^r2) {
		int m2=(l2+r2)/2;
		dc(2*i, l2, m2);
		dc(2*i+1, m2+1, r2);
	} else
		a2[l2]=ans*f1[l2+1]%M;
	while(st.size()>sts) {
		int y=st.back()[1], x=st.back()[0];
		ans=ans*f1[s[y]]%M;
		s[y]-=s[x];
		ans=ans*f2[s[x]]%M*f2[s[y]]%M;
		p[x]=x;
		st.pop_back();
	}
}

int main() {
	ifstream cin("circus.in");
	ofstream cout("circus.out");
	
	cin >> n;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	iv[1]=1;
	for(int i=2; i<=n; ++i)
		iv[i]=M-M/i*iv[M%i]%M;
	f1[0]=f2[0]=1;
	for(int i=1; i<=n; ++i) {
		f1[i]=f1[i-1]*i%M;
		f2[i]=f2[i-1]*iv[i]%M;
	}
	dfs1();
	dfs3();
	vector<int> st;
	for(; k<n; ++k) {
		int u=td[k];
		for(int v : adj[u]) {
			if(n-(md2[u]+2)>k)
				ae(k, n-(md2[u]+2)-1, {u, v});
			st.pop_back();
		}
		if(st.size()) {
			int v=st.back(), w=lca(u, v), d2=d[u]+d[v]-2*d[w];
			if(n-d2>k)
				ae(k, n-d2-1, {u, v});
		}
		st.push_back(u);
	}
	iota(p, p+n, 0);
	fill(s, s+n, 1);
	dc();
	for(int i=0; i<n; ++i)
		cout << a2[i] << "\n";
}
