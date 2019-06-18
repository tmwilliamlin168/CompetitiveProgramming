/*
	- The problem basically tells us that the graph is a cactus
	- Note that the game will end at the starting spot
	- dp1[u] = whether the player at node u can force a sequence of moves in the subtree to go back to node u and start his turn
	- dp2[u] = whether the player at node u can force a sequence of moves in the subtree to go back to node u and start the opponent's turn
	- We can do a second dfs to propagate the dp down from the root
	- In order to avoid quadratic complexity, we use a sparse table to calculate the dp within a BCC in O(logn) time
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, m, tin[mxN], low[mxN], dt=1, dp1[mxN][4], dp2[mxN], st[mxN], sh, bi, ans[mxN], ts, tl[19][mxN], tr[19][mxN];
vector<int> adj1[mxN], adj2[2*mxN];

int com(int f, int g) {
	return f&1?f:f^g;
}

int eval(int f) {
	f^=2;
	return f/2*3^f&1^1;
}

void ct(int t[19][mxN], vector<int> v) {
	ts=v.size();
	for(int i=0; i<ts; ++i)
		t[0][i]=dp1[v[i]][3]||dp1[v[i]][2]&1?3:2;
	for(int j=1; j<19; ++j)
		for(int i=0; i<=ts-(1<<j); ++i)
			t[j][i]=com(t[j-1][i], t[j-1][i+(1<<j-1)]);
}

int qry(int t[19][mxN], int l, int r) {
	if(r>=ts)
		return com(qry(t, l, ts-1), qry(t, 0, r-ts));
	int f=0;
	while(l<=r) {
		int k=31-__builtin_clz(r-l+1);
		f=com(f, t[k][l]);
		l+=1<<k;
	}
	return f;
}

void dfs1(int u=0, int p=-1) {
	tin[u]=low[u]=dt++;
	st[sh++]=u;
	for(int v : adj1[u]) {
		if(!tin[v]) {
			dfs1(v, u);
			low[u]=min(low[v], low[u]);
			if(low[v]>=tin[u]) {
				do {
					adj2[n+bi].push_back(st[--sh]);
				} while(st[sh]^v);
				ct(tl, adj2[n+bi]);
				reverse(adj2[n+bi].begin(), adj2[n+bi].end());
				ct(tr, adj2[n+bi]);
				dp2[bi]=eval(qry(tl, 0, adj2[n+bi].size()-1))|eval(qry(tr, 0, adj2[n+bi].size()-1));
				++dp1[u][dp2[bi]];
				adj2[u].push_back(n+bi++);
			}
		} else if(v^p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs2(int u=0, int p=1) {
	if(u<n) {
		++dp1[u][p];
		ans[u]=dp1[u][3]||dp1[u][2]&1?1:2;
		for(int v : adj2[u]) {
			--dp1[u][dp2[v-n]];
			dfs2(v, u);
			++dp1[u][dp2[v-n]];
		}
		--dp1[u][p];
	} else {
		vector<int> w=adj2[u], td(adj2[u].size());
		w.push_back(p);
		ct(tl, w);
		reverse(w.begin(), w.end());
		ct(tr, w);
		for(int i=0; i<adj2[u].size(); ++i)
			td[i]=eval(qry(tl, i+1, w.size()+i-1))|eval(qry(tr, adj2[u].size()-i+1, w.size()+adj2[u].size()-i-1));
		for(int i=0; i<adj2[u].size(); ++i)
			dfs2(adj2[u][i], td[i]);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0, a, b; i<m; ++i) {
		cin >> a >> b, --a, --b;
		adj1[a].push_back(b);
		adj1[b].push_back(a);
	}
	dfs1();
	dfs2();
	for(int i=0; i<n; ++i)
		cout << ans[i] << "\n";
}
