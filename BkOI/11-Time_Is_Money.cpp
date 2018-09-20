/*
	- http://www.boi2011.ro/resurse/tasks/timeismoney-sol.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=200;
int n, m, a[mxN][mxN], b[mxN][mxN], e[mxN];
array<ll, 2> a1={INT_MAX, INT_MAX}, r1;
vector<array<int, 2>> a2, r2;

array<ll, 2> prim(ll x, ll y) {
	r1={};
	r2={};
	memset(e, 0, 4*n);
	e[0]=-1;
	for(int it=0; it<n-1; ++it) {
		int mi=-1;
		for(int i=0; i<n; ++i)
			if(e[i]!=-1&&(mi==-1||x*a[i][e[i]]+y*b[i][e[i]]<x*a[mi][e[mi]]+y*b[mi][e[mi]]))
				mi=i;
		r1[0]+=a[mi][e[mi]];
		r1[1]+=b[mi][e[mi]];
		r2.push_back({mi, e[mi]});
		e[mi]=-1;
		for(int i=0; i<n; ++i)
			if(e[i]!=-1&&x*a[i][mi]+y*b[i][mi]<x*a[i][e[i]]+y*b[i][e[i]])
				e[i]=mi;
	}
	if(r1[0]*r1[1]<a1[0]*a1[1]) {
		a1=r1;
		a2=r2;
	}
	return r1;
}

void c(array<ll, 2> p1, array<ll, 2> p2) {
	array<ll, 2> p3=prim(p1[1]-p2[1], p2[0]-p1[0]);
	if((p2[0]-p1[0])*(p3[1]-p1[1])!=(p3[0]-p1[0])*(p2[1]-p1[1])) {
		c(p1, p3);
		c(p3, p2);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	memset(a, 1, sizeof(a));
	memset(b, 1, sizeof(b));
	while(m--) {
		int u, v;
		cin >> u >> v;
		cin >> a[u][v] >> b[u][v], a[v][u]=a[u][v], b[v][u]=b[u][v];
	}
	array<ll, 2> p1=prim(1, 0), p2=prim(0, 1);
	if(p1!=p2)
		c(p1, p2);
	cout << a1[0] << " " << a1[1] << "\n";
	for(array<int, 2> ai : a2)
		cout << ai[0] << " " << ai[1] << "\n";
}
