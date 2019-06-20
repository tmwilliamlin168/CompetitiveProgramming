#include <bits/stdc++.h>
using namespace std;

const int mxN=70;
int n, m, a, b, p[mxN], cs[mxN], cm[mxN], cc, ans[mxN], d[mxN][1<<mxN/4];
vector<array<int, 2>> adj[mxN];

int find(int u) {
	return p[u]^u?p[u]=find(p[u]):u;
}

int ma(int m, int c) {
	return ~c?m|1<<c:m;
}

int mb(int m, int c) {
	return ~c?m>>c&1:0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> a >> b;
	iota(p, p+n, 0);
	for(int i=0, u, v, c; i<m; ++i) {
		cin >> u >> v >> c, --u, --v;
		adj[u].push_back({c, v});
		adj[v].push_back({c, u});
		if(c^b)
			p[find(u)]=find(v);
	}
	for(int i=0; i<n; ++i)
		++cs[find(i)];
	for(int i=0; i<n; ++i)
		if(find(i)==i)
			cm[i]=cs[i]>3?cc++:-1;
	for(int i=0; i<n; ++i)
		cm[i]=cm[find(i)];
	priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;
	memset(d, 0x3f, sizeof(d));
	int sm=ma(0, cm[0]);
	d[0][sm]=0;
	pq.push({0, 0, sm});
	int ansleft=n;
	memset(ans, -1, 4*n);
	while(ansleft) {
		array<int, 3> u=pq.top();
		pq.pop();
		if(u[0]>d[u[1]][u[2]])
			continue;
		if(ans[u[1]]<0) {
			ans[u[1]]=u[0];
			--ansleft;
		}
		for(array<int, 2> v : adj[u[1]]) {
			int nm=ma(u[2], cm[v[1]]);
			if((!mb(u[2], cm[v[1]])&&find(u[1])^find(v[1])||v[0]^b)&&d[v[1]][nm]>u[0]+v[0]) {
				d[v[1]][nm]=u[0]+v[0];
				pq.push({u[0]+v[0], v[1], nm});
			}
		}
	}
	for(int i=0; i<n; ++i)
		cout << ans[i] << " ";
}
