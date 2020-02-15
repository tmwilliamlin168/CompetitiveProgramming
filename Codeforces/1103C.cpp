#include <bits/stdc++.h>
using namespace std;

const int mxN=2.5e5;
int n, m, k, p[mxN], d[mxN];
vector<int> adj[mxN];

void dfs(int u=0, int pu=-1) {
	p[u]=pu;
	d[u]=pu==-1?1:d[pu]+1;
	if(d[u]*k>=n) {
		cout << "PATH\n" << d[u] << "\n";
		for(; u!=-1; u=p[u])
			cout << u+1 << " ";
		exit(0);
	}
	for(int v : adj[u])
		if(!d[v])
			dfs(v, u);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for(int ui, vi; m--; ) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	dfs();
	cout << "CYCLES\n";
	for(int i=0, os=k; os; ++i) {
		bool ok=1;
		for(int j : adj[i])
			ok&=p[j]!=i;
		if(!ok)
			continue;
		for(int a=0; a<3&&ok; ++a) {
			for(int b=0; b<3&&ok; ++b) {
				if(d[adj[i][a]]<=d[adj[i][b]]||(d[adj[i][a]]-d[adj[i][b]])%3==1)
					continue;
				cout << d[adj[i][a]]-d[adj[i][b]]+2 << "\n" << i+1;
				for(int u=adj[i][a]; u!=adj[i][b]; u=p[u])
					cout << " " << u+1;
				cout << " " << adj[i][b]+1 << "\n";
				ok=0;
			}
		}
		--os;
	}
}
