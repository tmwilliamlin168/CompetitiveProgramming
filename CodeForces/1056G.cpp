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
	int a[mxATS], c[mxATS][2], s[mxATS], h[mxATS], ts=1;
	int cpy(int u, bool b=1) {
		if(!b)
			return u;
		a[ts]=a[u];
		c[ts][0]=c[u][0];
		c[ts][1]=c[u][1];
		s[ts]=s[u];
		h[ts]=h[u];
		return ts++;
	}
	void rcl(int u) {
		s[u]=s[c[u][0]]+1+s[c[u][1]];
		h[u]=max(h[c[u][0]], h[c[u][1]])+1;
	}
	void dfs(int u) {
		if(!u)
			return;
		dfs(c[u][0]);
		nxt[ni++][0]=a[u];
		dfs(c[u][1]);
	}
	bool hc(int u, int i) {
		return h[c[u][i]]-h[c[u][!i]]>1;
	}
	int ro(int u, int i) {
		int v=c[u][!i];
		c[u][!i]=c[v][i];
		c[v][i]=u;
		rcl(u);
		rcl(v);
		return v;
	}
	int rbl(int u, bool b=1) {
		for(int i : {0, 1}) {
			if(!hc(u, i))
				continue;
			u=cpy(u, b);
			int &v=c[u][i]=cpy(c[u][i]);
			if(h[c[v][!i]]>h[c[v][i]]) {
				c[v][!i]=cpy(c[v][!i]);
				v=ro(v, i);
			}
			u=ro(u, !i);
		}
		return u;
	}
	int rbl2(int u, bool b=1) {
		bool d[2]={hc(u, 0), hc(u, 1)};
		if(!d[0]&&!d[1])
			return u;
		u=rbl(u, b);
		for(int i : {0, 1}) {
			if(!d[i])
				continue;
			if(h[c[u][i]]>h[c[u][!i]]) {
				c[u][i]=cpy(c[u][i]);
				u=ro(u, !i);
				c[c[u][!i]][!i]=rbl2(c[c[u][!i]][!i]);
			} else
				c[u][!i]=rbl2(c[u][!i]);
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
			c[w][1]=mrg(c[w][1], v);
		} else {
			w=cpy(v);
			c[w][0]=mrg(u, c[w][0]);
		}
		rcl(w);
		return rbl(w, 0);
	}
	ar<int, 2> spl(int u, int k) {
		if(!u)
			return {0, 0};
		u=cpy(u);
		if(k<=s[c[u][0]]) {
			ar<int, 2> a=spl(c[u][0], k);
			c[u][0]=a[1];
			u=rbl2(u, 0);
			rcl(u);
			return {a[0], u};
		} else {
			ar<int, 2> a=spl(c[u][1], k-s[c[u][0]]-1);
			c[u][1]=a[0];
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
