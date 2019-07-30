#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxSTS=mxN*18*3;
int n, m, k, d[mxN], w[mxN], rt[mxN], sts=1, lc[mxSTS], rc[mxSTS];
vector<int> adj[mxN];
ll st1[mxSTS], st2[mxSTS], lz2[mxSTS];
bool lz1[mxSTS];

void app(int &i, bool b, ll x) {
	if(!i)
		i=sts++;
	if(b) {
		st1[i]=0;
		st2[i]=0;
		lz1[i]=1;
		lz2[i]=0;
	}
	st1[i]+=x;
	st2[i]+=x;
	lz2[i]+=x;
}

void psh(int i) {
	app(lc[i], lz1[i], lz2[i]);
	app(rc[i], lz1[i], lz2[i]);
	lz1[i]=lz2[i]=0;
}

void mrg(int &i, int j, int l2=0, int r2=k-1) {
	if(!lc[i])
		swap(i, j);
	if(!lc[j]) {
		app(i, 0, st1[j]);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	psh(j);
	mrg(lc[i], lc[j], l2, m2);
	mrg(rc[i], rc[j], m2+1, r2);
	st1[i]=min(st1[lc[i]], st1[rc[i]]);
	st2[i]=max(st2[lc[i]], st2[rc[i]]);
}

void upd(int i, int l1, int r1, ll x, int l2=0, int r2=k-1) {
	if(st1[i]>x)
		return;
	if(l1<=l2&&r2<=r1&&st2[i]<=x) {
		app(i, 1, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(lc[i], l1, r1, x, l2, m2);
	if(m2<r1)
		upd(rc[i], l1, r1, x, m2+1, r2);
	st1[i]=min(st1[lc[i]], st1[rc[i]]);
	st2[i]=max(st2[lc[i]], st2[rc[i]]);
}

ll qry(int i, int l1, int l2=0, int r2=k-1) {
	if(l2==r2)
		return st1[i];
	int m2=(l2+r2)/2;
	psh(i);
	return l1<=m2?qry(lc[i], l1, l2, m2):qry(rc[i], l1, m2+1, r2);
}

void dfs(int u=0) {
	rt[u]=sts++;
	for(int v : adj[u]) {
		dfs(v);
		mrg(rt[u], rt[v]);
	}
	upd(rt[u], d[u], k-1, qry(rt[u], d[u])+w[u]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> m >> k;
	for(int i=1, p; i<n; ++i) 
		cin >> p, --p, adj[p].push_back(i);
	for(int v, dj, wj; m--; ) {
		cin >> v >> dj >> wj, --v, --dj;
		d[v]=dj;
		w[v]=wj;
	}
	dfs();
	cout << st2[rt[0]];
}
