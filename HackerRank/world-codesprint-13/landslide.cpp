/*
	- Dynamic connectivity with persistent dsu
	- Instead of dividing the segments into parts of a segment tree, this uses square root decomposition
	- Use "lazy propagation" for O(n) memory instead of O(nsqrt(n))
	- Non-asymptotic optimizations required
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=2e5, sqN=438;
int n, q, qb, x[mxN-1], y[mxN-1], f[mxN], depT[19][2*mxN-1], dti, l[mxN-1], p[mxN], s[mxN], dp[mxN];
vector<int> adj[mxN];
unordered_map<long long, int> mp;
vector<pii> ops, e1[(mxN-1)/sqN+1], e2[mxN], e3[mxN];

void dfs(int u, int p, int d) {
	f[u]=dti;
	depT[0][dti++]=d;
	for(int v : adj[u]) {
		if(v==p)
			continue;
		dfs(v, u, d+1);
		depT[0][dti++]=d;
	}
}

inline int dist(int u, int v) {
	if(f[u]>f[v])
		swap(u, v);
	int k=31-__builtin_clz(f[v]-f[u]);
	return depT[0][f[u]]+depT[0][f[v]]-2*min(depT[k][f[u]], depT[k][f[v]-(1<<k)+1]);
}

inline void ins(int l, int r, int x) {
	if(l>r)
		return;
	if(l%sqN==0&&min(l+sqN, q)-1<=r)
		e1[l/sqN].push_back({x, r});
	else
		e2[l].push_back({x, r});
}

inline int find(int x) {
	return x==p[x]?x:find(p[x]);
}

inline void join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return;
	if(s[x]<s[y])
		swap(x, y);
	p[y]=x;
	s[x]+=s[y];
	ops.push_back({x, y});
}

inline void undo() {
	p[ops.back().se]=ops.back().se;
	s[ops.back().fi]-=s[ops.back().se];
	ops.pop_back();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n-1; ++i) {
		cin >> x[i] >> y[i], --x[i], --y[i];
		if(x[i]<y[i])
			swap(x[i], y[i]);
		adj[x[i]].push_back(y[i]);
		adj[y[i]].push_back(x[i]);
		mp[(long long)x[i]*n+y[i]]=i;
	}
	dfs(0, -1, 0);
	for(int i=1; i<19; ++i)
		for(int j=0; j<2*n-(1<<i); ++j)
			depT[i][j]=min(depT[i-1][j], depT[i-1][j+(1<<(i-1))]);
	cin >> q;
	char lqt='d';
	for(int i=0; i<q; ++i) {
		char qt;
		int qx, qy, qi;
		cin >> qt >> qx >> qy, --qx, --qy;
		if(qx<qy)
			swap(qx, qy);
		if(qt=='q') {
			if(lqt!='d')
				--i, --q;
			e3[i].push_back({qx, qy});
			lqt='q';
			continue;
		}
		auto it=mp.find((long long)qx*n+qy);
		if(it==mp.end())
			continue;
		qi=it->second;
		if(qt=='d') {
			if(i)
				--i, --q;
			if(l[qi]!=-1) {
				ins(l[qi], i, qi);
				l[qi]=-1;
			}
		} else if(l[qi]==-1) {
			if(lqt=='c')
				--i, --q;
			l[qi]=i;
		}
		lqt=qt;
	}
	qb=(q-1)/sqN+1;
	dp[q-1]=q;
	for(int i=q-2; i>=0; --i)
		dp[i]=!e3[i+1].empty()?i+1:min(dp[i+1], (i/sqN+1)*sqN);
	for(int i=0; i<n-1; ++i)
		if(l[i]!=-1)
			ins(l[i], q-1, i);
	for(int i=0; i<qb; ++i) {
		for(int j=0; j<n; ++j)
			p[j]=j, s[j]=1;
		for(pii j : e1[i]) {
			join(x[j.fi], y[j.fi]);
			ins((i+1)*sqN, j.se, j.fi);
		}
		int opss=ops.size();
		for(int j=i*sqN; j<min((i+1)*sqN, q); ++j) {
			if(!e3[j].empty()) {
				for(pii k : e2[j])
					join(x[k.fi], y[k.fi]);
				for(pii k : e3[j]) {
					if(find(k.fi)==find(k.se))
						cout << dist(k.fi, k.se) << "\n";
					else
						cout << "Impossible\n";
				}
				while(ops.size()>opss)
					undo();
			}
			for(pii k : e2[j])
				ins(dp[j], k.se, k.fi);
			vector<pii>().swap(e2[j]);
		}
		vector<pii>().swap(e1[i]);
		ops.clear();
	}
}
