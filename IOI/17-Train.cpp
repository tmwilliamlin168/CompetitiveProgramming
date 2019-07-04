/*
	- In 1 round
		- Happen simultaneously, like toposort
			- Label unlabeled charging stations as winning
			- Label unlabeled stations A owns going into any winning stations as winning
			- Label unlabeled stations B owns only going into winning stations as winning
		- Quit if there are no unlabeled stations left
		- Label all unlabeled stations as losing
		- Label all winning stations as unlabeled
		- Happen simultaneously, like toposort
			- Label unlabeled stations A owns only going into losing stations as losing
			- Label unlabeled stations B owns going into any losing stations as losing
	- All stations will be labeled after at most n rounds
*/

#include "train.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=5e3;
int n, w[mxN], d[mxN][2], b[mxN];
vector<int> adj[mxN];
queue<int> qu;

vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
	n=a.size();
	for(int i=0; i<u.size(); ++i) {
		adj[v[i]].push_back(u[i]);
		++b[u[i]];
	}
	memset(w, -1, 4*n);
	while(1) {
		for(int i=0; i<n; ++i) {
			if(w[i]<0&&(r[i]||d[i][1]>=(a[i]?1:b[i]))) {
				w[i]=1;
				qu.push(i);
			}
		}
		while(qu.size()) {
			int u=qu.front();
			qu.pop();
			for(int v : adj[u]) {
				++d[v][1];
				if(w[v]<0&&d[v][1]>=(a[v]?1:b[v])) {
					w[v]=1;
					qu.push(v);
				}
			}
		}
		bool c=1;
		for(int i=0; i<n&&c; ++i)
			c=~w[i];
		if(c)
			break;
		for(int i=0; i<n; ++i) {
			if(w[i]<0) {
				w[i]=0;
				for(int v : adj[i])
					++d[v][0];
			}
			if(w[i]) {
				w[i]=-1;
				for(int v : adj[i])
					--d[v][1];
			}
		}
		for(int i=0; i<n; ++i) {
			if(w[i]&&d[i][0]>=(a[i]?b[i]:1)) {
				w[i]=0;
				qu.push(i);
			}
		}
		while(qu.size()) {
			int u=qu.front();
			qu.pop();
			for(int v : adj[u]) {
				++d[v][0];
				if(w[v]&&d[v][0]>=(a[v]?b[v]:1)) {
					w[v]=0;
					qu.push(v);
				}
			}
		}
	}
	return vector<int>(w, w+n);
}
