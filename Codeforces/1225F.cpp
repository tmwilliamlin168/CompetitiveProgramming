#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, p[mxN], a1[mxN], a1i;
vector<int> adj[mxN], a2;
array<int, 2> d[mxN];

void dfs(int u=0) {
	d[u][1]=u;
	for(int v : adj[u]) {
		d[v][0]=d[u][0]+1;
		dfs(v);
	}
	for(int v : adj[u])
		d[u]=max(d[v], d[u]);
	sort(adj[u].begin(), adj[u].end(), [](const int &i, const int &j) {
		return d[i]<d[j];
	});
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1; i<n; ++i) {
		cin >> p[i];
		adj[p[i]].push_back(i);
	}
	dfs();
	int u=d[0][1];
	a1[--(a1i=n)]=u;
	while(u) {
		if(adj[p[u]].size()<2) {
			u=p[u];
			a1[--a1i]=u;
		} else {
			adj[p[u]].pop_back();
			p[u]=adj[p[u]].back();
			adj[p[u]].push_back(u);
			a2.push_back(u);
		}
	}
	for(int i=0; i<n; ++i)
		cout << a1[i] << " ";
	cout << "\n" << a2.size() << "\n";
	reverse(a2.begin(), a2.end());
	for(int b : a2)
		cout << b << " ";
}
