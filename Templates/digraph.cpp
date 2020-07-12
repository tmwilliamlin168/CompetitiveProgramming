struct digraph {
	int n;
	vt<vt<int>> adj, adj2;
	digraph(int _n, vt<ar<int, 2>> &e) {
		n=_n;
		adj=vt<vt<int>>(n);
		adj2=vt<vt<int>>(n);
		EACH(a, e) {
			adj[a[0]].pb(a[1]);
			adj2[a[1]].pb(a[0]);
		}
	}
	vt<int> toposort() {
		vt<int> d(n);
		queue<int> qu;
		FOR(n) {
			d[i]=sz(adj2[i]);
			if(!d[i])
				qu.push(i);
		}
		vt<int> ans;
		while(qu.size()) {
			int u=qu.front();
			qu.pop();
			EACH(v, adj[u]) {
				--d[v];
				if(!d[v])
					qu.push(v);
			}
			ans.pb(u);
		}
		if(sz(ans)<n)
			ans.clear();
		return ans;
	}
};
