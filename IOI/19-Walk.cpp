#include "walk.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e5, mxT=1e6;
int n, m, pg[mxN], t, ua, ub;
vector<int> ta[mxN], tr[mxN];
ll d[mxT];
vector<ar<ll, 2>> adj[mxT];

ll min_distance(vector<int> x, vector<int> h, vector<int> l, vector<int> r, vector<int> y, int a, int b) {
	n=x.size();
	m=l.size();
	vector<vector<int>> v(n);
	v[a].push_back(0);
	v[b].push_back(0);
	for(int _ : {1, 0}) {
		for(int i=0; i<m; ++i) {
			ta[l[i]].push_back(i);
			tr[r[i]].push_back(i);
		}
		set<ar<int, 2>> s;
		for(int i=0; i<n; ++i) {
			vector<ar<int, 2>> w;
			for(pg[i]=i-1; ~pg[i]&&h[pg[i]]<=h[i]; pg[i]=pg[pg[i]]) {
				auto it=s.lower_bound({h[pg[i]]});
				if(it!=s.end()&&(*it)[0]<=h[i])
					w.push_back(*it);
			}
			for(int j : ta[i])
				s.insert({y[j], j});
			for(auto a : w) {
				v[i].push_back(a[0]);
				auto it=s.upper_bound(a);
				if(it!=s.end()&&(*it)[0]<=h[i])
					v[i].push_back((*it)[0]);
			}
			for(int j : ta[i]) {
				v[i].push_back(y[j]);
				auto it=s.upper_bound({y[j], j});
				if(it!=s.end()&&(*it)[0]<=h[i])
					v[i].push_back((*it)[0]);
				if(--it!=s.begin())
					v[i].push_back((*--it)[0]);
			}
			if(_&&(i==a||i==b)&&s.size()&&(*s.begin())[0]<=h[i])
				v[i].push_back((*s.begin())[0]);
			for(int j : tr[i])
				s.erase({y[j], j});
			ta[i].clear();
			tr[i].clear();
		}
		reverse(h.begin(), h.end());
		for(int i=0; i<m; ++i)
			tie(l[i], r[i])=make_pair(n-1-r[i], n-1-l[i]);
		reverse(v.begin(), v.end());
	}
	unordered_map<int, int> m1;
	unordered_map<int, ar<int, 3>> m2;
	for(int i=0; i<m; ++i)
		ta[l[i]].push_back(i);
	for(int i=0; i<n; t+=v[i++].size()) {
		if(i==a)
			ua=t;
		if(i==b)
			ub=t;
		for(int j : ta[i])
			m1[y[j]]=r[j]+1;
		sort(v[i].begin(), v[i].end());
		v[i].resize(unique(v[i].begin(), v[i].end())-v[i].begin());
		for(int j=0; j+1<v[i].size(); ++j) {
			adj[t+j].push_back({v[i][j+1]-v[i][j], t+j+1});
			adj[t+j+1].push_back({v[i][j+1]-v[i][j], t+j});
		}
		for(int j=0; j<v[i].size(); ++j) {
			auto a=m2[v[i][j]];
			if(a[2]>i) {
				adj[a[0]].push_back({x[i]-x[a[1]], t+j});
				adj[t+j].push_back({x[i]-x[a[1]], a[0]});
			}
			m2[v[i][j]]={t+j, i, m1[v[i][j]]};
		}
	}
	memset(d, 0x3f, 8*t);
	priority_queue<ar<ll, 2>, vector<ar<ll, 2>>, greater<ar<ll, 2>>> pq;
	d[ua]=0;
	pq.push({0, ua});
	while(pq.size()) {
		ar<ll, 2> u=pq.top();
		pq.pop();
		if(u[0]>d[u[1]])
			continue;
		for(auto v : adj[u[1]]) {
			if(d[v[1]]>u[0]+v[0]) {
				d[v[1]]=u[0]+v[0];
				pq.push({d[v[1]], v[1]});
			}
		}
	}
	return d[ub]>2e14?-1:d[ub];
}
