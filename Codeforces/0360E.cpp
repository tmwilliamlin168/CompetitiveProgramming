/*
	- First consider the case of checking if d1[f] < d2[f]
	- If d1[a] < d2[a], then all edges out of a should be set to the minimum cost possible
	- Otherwise, they should be set to the maximum cost possible
	- We can just run dijkstra from both sources
	- Checking if d1[f] <= d2[f] is similar
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

const int mxN=1e4, mxM=10100;
int n, m, k, s1, s2, f, a[mxM], b[mxM], c[2][mxM], c2[mxM];
vector<int> adj[mxN];
ll d1[mxN], d2[mxN];

void chk(int x) {
	memset(d1, 0x3f, sizeof(d1));
	memset(d2, 0x3f, sizeof(d2));
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	d1[s1]=d2[s2]=0;
	pq.push({0, s1});
	pq.push({0, s2});
	while(pq.size()) {
		pli u=pq.top();
		pq.pop();
		if(u.first>min(d1[u.second], d2[u.second]))
			continue;
		bool f=d1[u.second]>=d2[u.second]+x;
		for(int e : adj[u.second]) {
			c2[e]=f;
			if(d1[u.second]+c[f][e]<d1[b[e]]) {
				d1[b[e]]=d1[u.second]+c[f][e];
				pq.push({d1[b[e]], b[e]});
			}
			if(d2[u.second]+c[f][e]<d2[b[e]]) {
				d2[b[e]]=d2[u.second]+c[f][e];
				pq.push({d2[b[e]], b[e]});
			}
		}
	}
	if(d1[f]>=d2[f]+x)
		return;
	cout << (x?"DRAW":"WIN") << "\n";
	for(int i=0; i<k; ++i)
		cout << c[c2[i]][i] << " ";
	exit(0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k >> s1 >> s2 >> f, --s1, --s2, --f;
	for(int i=0; i<m; ++i)
		cin >> a[k+i] >> b[k+i] >> c[0][k+i], --a[k+i], --b[k+i], c[1][k+i]=c[0][k+i];
	for(int i=0; i<k; ++i)
		cin >> a[i] >> b[i] >> c[0][i] >> c[1][i], --a[i], --b[i];
	for(int i=0; i<k+m; ++i)
		adj[a[i]].push_back(i);
	chk(0);
	chk(1);
	cout << "LOSE";
}
