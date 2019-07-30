#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const int mxN=1e5;
int n, q, eu[mxN], ev[mxN], dt, ds[mxN], de[mxN];
ll w, ew[mxN], lz[1<<19], ans;
vector<int> adj[mxN];
array<ll, 5> st[1<<19];
 
void app(int i, ll x) {
	st[i][0]+=x;
	st[i][1]-=2*x;
	st[i][2]-=x;
	st[i][3]-=x;
	lz[i]+=x;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
}

void upd(int l1, int r1, ll x, int i=1, int l2=0, int r2=2*n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	st[i][0]=max(st[2*i][0], st[2*i+1][0]);
	st[i][1]=max(st[2*i][1], st[2*i+1][1]);
	st[i][2]=max({st[2*i][2], st[2*i+1][2], st[2*i][0]+st[2*i+1][1]});
	st[i][3]=max({st[2*i][3], st[2*i+1][3], st[2*i][1]+st[2*i+1][0]});
	st[i][4]=max({st[2*i][4], st[2*i+1][4], st[2*i][2]+st[2*i+1][0], st[2*i][0]+st[2*i+1][3]});
}

void dfs(int u=0, int pe=n-1) {
	ds[pe]=dt++;
	for(int e : adj[u]) {
		if(e==pe)
			continue;
		dfs(eu[e]^ev[e]^u, e);
		upd(ds[e], de[e]-1, ew[e]);
		++dt;
	}
	de[pe]=dt;
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> q >> w;
	for(int i=0; i<n-1; ++i) {
		cin >> eu[i] >> ev[i] >> ew[i], --eu[i], --ev[i];
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
	}
	dfs();
	while(q--) {
		int dj;
		ll ej;
		cin >> dj >> ej;
		dj=(dj+ans)%(n-1);
		ej=(ej+ans)%w;
		upd(ds[dj], de[dj]-1, ej-ew[dj]);
		ew[dj]=ej;
		cout << (ans=st[1][4]) << "\n";
	}
}
