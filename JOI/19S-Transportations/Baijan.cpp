#include "Baijan.h"
#include <bits/stdc++.h>
using namespace std;

namespace {
	int ld, st;
	array<int, 2> u;
	queue<bool> bs;
	vector<int> d;
	vector<array<int, 2>> adj[2000];
	priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
	bool s[2000];

	void sendInt(int x, int d) {
		for(int i=0; i<d; ++i)
			SendB(x>>i&1);
	}

	int readInt(int d) {
		int r=0;
		for(int i=0; i<d; ++i) {
			r|=bs.front()<<i;
			bs.pop();
		}
		return r;
	}

	void an() {
		if(u[0]>ld+500)
			return;
		d[u[1]]=u[0];
		s[u[1]]=1;
		for(array<int, 2> v : adj[u[1]]) {
			if(u[0]+v[0]<d[v[1]]) {
				d[v[1]]=u[0]+v[0];
				pq.push({d[v[1]], v[1]});
			}
		}
		ld=u[0];
		u={1, 0};
		while(pq.size()&&s[u[1]]) {
			u=pq.top();
			pq.pop();
		}
		if(s[u[1]])
			u[0]=ld+501;
		sendInt(u[0]-ld, 9);
		st=1;
	}
};

void InitB(int n, int b, vector<int> s, vector<int> t, vector<int> c) {
	for(int i=0; i<b; ++i) {
		adj[s[i]].push_back({c[i], t[i]});
		adj[t[i]].push_back({c[i], s[i]});
	}
	d=vector<int>(n, 1e9);
	an();
}

void ReceiveB(bool x) {
	bs.push(x);
	if(st==1) {
		if(bs.size()<9)
			return;
		int od=readInt(9);
		if(ld+od<=u[0]) {
			pq.push(u);
			u[0]=ld+od;
			st=2;
		} else {
			sendInt(u[1], 11);
			an();
		}
	} else if(st==2) {
		if(bs.size()<11)
			return;
		u[1]=readInt(11);
		an();
	}
}
