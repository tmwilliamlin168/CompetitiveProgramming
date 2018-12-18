#include <bits/stdc++.h>
using namespace std;

#define a array

const int mxN=5e4, BIG=1e9;
int n, m, k, y[mxN], ai, bi, ti, d1[mxN];
a<int, 2> d2[mxN];
vector<a<int, 2>> adj[mxN];

void dijkstra1() {
	//first dijkstra from n
	priority_queue<a<int, 2>, vector<a<int, 2>>, greater<a<int, 2>>> pq;
	memset(d1, 0x7f, 4*n);
	d1[n-1]=0;
	pq.push({0, n-1});
	while(pq.size()) {
		a<int, 2> u=pq.top();
		pq.pop();
		if(u[0]>d1[u[1]])
			continue;
		for(a<int, 2> v : adj[u[1]]) {
			if(d1[v[1]]>u[0]+v[0]) {
				d1[v[1]]=u[0]+v[0];
				pq.push({d1[v[1]], v[1]});
			}
		}
	}
}

void dijkstra2() {
	//multi-source dijkstra
	//we also keep track of the source
	//sources that are not node n mean that haybales are possible
	//distances are stored as a pair {distance, source}
	priority_queue<a<int, 3>, vector<a<int, 3>>, greater<a<int, 3>>> pq;
	memset(d2, 0x7f, sizeof(d2[0])*n);
	d2[n-1]={BIG, n-1};
	pq.push({BIG, n-1, n-1});
	//add other nodes with haybales as sources
	for(int i=0; i<n-1; ++i) {
		if(!y[i])
			continue;
		d2[i]={d1[i]+BIG-y[i], i};
		pq.push({d1[i]+BIG-y[i], i, i});
	}
	while(pq.size()) {
		a<int, 3> u=pq.top();
		pq.pop();
		if(a<int, 2>{u[0], u[1]}>d2[u[2]])
			continue;
		for(a<int, 2> v : adj[u[2]]) {
			if(d2[v[1]]>a<int, 2>{u[0]+v[0], u[1]}) {
				d2[v[1]]={u[0]+v[0], u[1]};
				pq.push({u[0]+v[0], u[1], v[1]});
			}
		}
	}
}

int main() {
	ifstream cin("dining.in");
	ofstream cout("dining.out");
	
	//input
	cin >> n >> m >> k;
	while(m--) {
		cin >> ai >> bi >> ti, --ai, --bi;
		adj[ai].push_back({ti, bi});
		adj[bi].push_back({ti, ai});
	}
	while(k--) {
		cin >> ai >> bi, --ai;
		y[ai]=max(bi, y[ai]);
	}
	dijkstra1();
	dijkstra2();
	//output
	//if there is a haybale at node n, all answers are 1
	for(int i=0; i<n-1; ++i)
		cout << (d2[i][1]<n-1||y[n-1]) << "\n";
}
