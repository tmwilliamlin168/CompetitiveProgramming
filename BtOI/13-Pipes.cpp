/*
	- Multiple answers if there is an even cycle
		- Two odd cycles also have the same effect
	- All the leaf edges can be determined and removed
	- Left with at most one cycle, the edge weights can be determined with simple algebra
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, m, eu[mxN], ev[mxN], d[mxN], qu[mxN-1], qt, nx[mxN];
ll a[mxN], b[mxN];
vector<int> adj[mxN];

void fk() {
	cout << 0;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	if(m>n)
		fk();
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<m; ++i) {
		cin >> eu[i] >> ev[i], --eu[i], --ev[i];
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
		++d[eu[i]];
		++d[ev[i]];
	}
	for(int i=0; i<n; ++i)
		if(d[i]==1)
			qu[qt++]=i;
	for(int qh=0; qh<n-1; ++qh) {
		if(qh>=qt) {
			if((n^qh)&1^1)
				fk();
			int u=-1, l=-1;
			while(!d[++u]);
			ll s1=0;
			for(int v=u, w, s2=1; v!=u||l==-1; l=nx[v], v=w, s2=-s2) {
				for(int e : adj[v]) {
					nx[v]=e;
					w=v^eu[e]^ev[e];
					if(d[w]&&e!=l)
						break;
				}
				s1+=s2*a[v];
			}
			b[l]=s1;
			for(int v=u, w; nx[v]!=l; v^=eu[nx[v]]^ev[nx[v]])
				b[nx[v]]=s1=2*a[v]-s1;
			a[0]=0;
			break;
		}
		int u=qu[qh];
		for(int e : adj[u]) {
			int v=u^eu[e]^ev[e];
			if(!d[v])
				continue;
			b[e]=2*a[u];
			a[v]-=a[u];
			if(--d[v]==1)
				qu[qt++]=v;
			break;
		}
		d[u]=0;
	}
	if(a[qu[n-1]])
		fk();
	for(int i=0; i<m; ++i)
		cout << b[i] << "\n";
}
