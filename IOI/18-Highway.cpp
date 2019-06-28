/*
	- Find the cost of the shortest path without heavy traffic with 1 query
	- We can binary search to find any edge (a, b) in any shortest path with 17 queries
	- Note that there exists a shortest path using the edges from the union of the 2 bfs spanning trees from a and b
	- If a shortest path looks like s - c - a - b - t, dist(a, c) < dist(b, c)
		- We can reduce the 2 bfs spanning trees to have no nodes in common
	- We can use binary search, blocking the edges farther from a/b, to find both s and t in a total of 32 queries
*/

#include "highway.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=9e4;
int m, d1[mxN], d2[mxN], me;
vector<int> eu, ev, adj[mxN];
vector<array<int, 2>> p1, p2;
long long bc;

void bfs(int s, int d[mxN], vector<array<int, 2>> &p) {
	memset(d, 0x3f, 4*mxN);
	d[s]=0;
	p.push_back({s});
	for(int qh=0; qh<p.size(); ++qh) {
		int u=p[qh][0];
		for(int e : adj[u]) {
			int v=eu[e]^ev[e]^u;
			if(d[v]>d[u]+1) {
				d[v]=d[u]+1;
				p.push_back({v, e});
			}
		}
	}
}

int solve(int d1[mxN], int d2[mxN], vector<array<int, 2>> p1, vector<array<int, 2>> p2) {
	vector<array<int, 2>> q;
	for(array<int, 2> a : p1)
		if(d1[a[0]]<d2[a[0]])
			q.push_back(a);
	int lb=0, rb=q.size()-1;
	while(lb<rb) {
		int mb=(lb+rb+1)/2;
		vector<int> w(m, 1);
		w[me]=0;
		for(int i=0; i<mb; ++i)
			w[q[i][1]]=0;
		for(array<int, 2> a : p2)
			if(d2[a[0]]<d1[a[0]])
				w[a[1]]=0;
		if(ask(w)>bc)
			lb=mb;
		else
			rb=mb-1;
	}
	return q[lb][0];
}

void find_pair(int n, vector<int> u, vector<int> v, int a, int b) {
	eu=u;
	ev=v;
	m=u.size();
	for(int i=0; i<m; ++i) {
		adj[u[i]].push_back(i);
		adj[v[i]].push_back(i);
	}
	bc=ask(vector<int>(m));
	int lb=0, rb=m-1;
	while(lb<rb) {
		int mb=(lb+rb)/2;
		vector<int> w(m);
		fill(w.begin(), w.begin()+mb+1, 1);
		if(ask(w)>bc)
			rb=mb;
		else
			lb=mb+1;
	}
	me=lb;
	bfs(u[me], d1, p1);
	bfs(v[me], d2, p2);
	answer(solve(d1, d2, p1, p2), solve(d2, d1, p2, p1));
}
