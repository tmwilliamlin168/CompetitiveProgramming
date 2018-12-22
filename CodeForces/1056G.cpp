/*
	- Rebalance
		- WLOG h[lc]>h[rc]+1
		- a=lc.lc, b=lc.rc, c=rc
		- If h[b]<=h[a], use simple right rotation to fix
		- Else, bring b up to the root
	- Merge
		- Merge small to large
		- Large tree's child's height won't change too much
		- One rebalance makes the final tree avl
	- Split
		- After splitting, try to rebalance the root node first
		- We will need to rebalance the subtrees later
		- Note that the subtrees will only decrease in height, so we should try to rotate so that subtrees we are trying to fix will be higher
		- Each split takes like O(h1-h2), which will total up to O(logn) per split
*/

#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5, mxATS=2.2e7;
int n, m, s, dp, nxt[mxN][40], ni;
long long t;

struct avltree {
	int a[mxATS], lc[mxATS], rc[mxATS], s[mxATS], h[mxATS], ts=1;
	int cpy(int u, bool b=1) {
		if(!b)
			return u;
		a[ts]=a[u];
		lc[ts]=lc[u];
		rc[ts]=rc[u];
		s[ts]=s[u];
		h[ts]=h[u];
		return ts++;
	}
	void rcl(int u) {
		s[u]=s[lc[u]]+1+s[rc[u]];
		h[u]=max(h[lc[u]], h[rc[u]])+1;
	}
	void dfs(int u) {
		if(!u)
			return;
		dfs(lc[u]);
		nxt[ni++][0]=a[u];
		dfs(rc[u]);
	}
	bool hl(int u) {
		return h[lc[u]]-h[rc[u]]>1;
	}
	bool hr(int u) {
		return h[rc[u]]-h[lc[u]]>1;
	}
	int rr(int u) {
		int v=lc[u];
		lc[u]=rc[v];
		rc[v]=u;
		rcl(u);
		rcl(v);
		return v;
	}
	int rl(int u) {
		int v=rc[u];
		rc[u]=lc[v];
		lc[v]=u;
		rcl(u);
		rcl(v);
		return v;
	}
	int rbl(int u, bool b=1) {
		if(hl(u)) {
			u=cpy(u, b);
			lc[u]=cpy(lc[u]);
			if(h[rc[lc[u]]]>h[lc[lc[u]]]) {
				rc[lc[u]]=cpy(rc[lc[u]]);
				lc[u]=rl(lc[u]);
			}
			u=rr(u);
		} else if(hr(u)) {
			u=cpy(u, b);
			rc[u]=cpy(rc[u]);
			if(h[lc[rc[u]]]>h[rc[rc[u]]]) {
				lc[rc[u]]=cpy(lc[rc[u]]);
				rc[u]=rr(rc[u]);
			}
			u=rl(u);
		}
		return u;
	}
	int rbl2(int u, bool b=1) {
		bool b1=hl(u), b2=hr(u);
		if(!b1&&!b2)
			return u;
		u=rbl(u, b);
		if(b1) {
			if(h[rc[u]]<h[lc[u]]) {
				lc[u]=cpy(lc[u]);
				u=rr(u);
				rc[rc[u]]=rbl2(rc[rc[u]]);
			} else
				rc[u]=rbl2(rc[u]);
		} else {
			if(h[lc[u]]<h[rc[u]]) {
				rc[u]=cpy(rc[u]);
				u=rl(u);
				lc[lc[u]]=rbl2(lc[lc[u]]);
			} else
				lc[u]=rbl2(lc[u]);
		}
		rcl(u);
		return u;
	}
	int mrg(int u, int v) {
		if(!u||!v)
			return u^v;
		int w;
		if(h[u]>h[v]) {
			w=cpy(u);
			rc[w]=mrg(rc[w], v);
		} else {
			w=cpy(v);
			lc[w]=mrg(u, lc[w]);
		}
		rcl(w);
		return rbl(w, 0);
	}
	ar<int, 2> spl(int u, int k) {
		if(!u)
			return {0, 0};
		u=cpy(u);
		if(k<=s[lc[u]]) {
			ar<int, 2> a=spl(lc[u], k);
			lc[u]=a[1];
			u=rbl2(u, 0);
			rcl(u);
			return {a[0], u};
		} else {
			ar<int, 2> a=spl(rc[u], k-s[lc[u]]-1);
			rc[u]=a[0];
			u=rbl2(u, 0);
			rcl(u);
			return {u, a[1]};
		}
	}
} at;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> s >> t, --s;
	for(int i=0; i<n; ++i) {
		at.a[at.ts]=i;
		at.s[at.ts]=at.h[at.ts]=1;
		dp=at.mrg(dp, at.ts++);
	}
	for(int i=1; i<n; ++i) {
		ar<int, 2> a=at.spl(dp, i);
		int dp1, dp2;
		if(n-i<m) {
			ar<int, 2> b=at.spl(a[0], m-n+i);
			dp1=at.mrg(a[1], b[0]);
		} else
			dp1=at.spl(a[1], m)[0];
		a=at.spl(dp, n-i);
		if(i>m) {
			ar<int, 2> b=at.spl(a[1], m);
			dp2=at.mrg(b[1], a[0]);
		} else
			dp2=at.spl(a[0], m-i)[1];
		dp=at.mrg(dp1, dp2);
	}
	at.dfs(dp);
	while(t%n) {
		if(s<m)
			s=(s+t)%n;
		else
			s=(s-t%n+n)%n;
		--t;
	}
	t/=n;
	for(int i=1; i<40; ++i)
		for(int j=0; j<n; ++j)
			nxt[j][i]=nxt[nxt[j][i-1]][i-1];
	for(int i=39; i>=0; --i) {
		if(t>=1ll<<i) {
			t-=1ll<<i;
			s=nxt[s][i];
		}
	}
	cout << s+1;
}
