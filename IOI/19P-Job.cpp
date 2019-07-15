/*
	- If there were no tree requirement, we would process jobs starting from small d[i]/u[i]
	- We iterate through nodes starting from the leaves
	- If a node has greater d[i]/u[i] than any one of its children, merge it with the child with the smallest d[i]/u[i]
	- In the end we end up with a tree such that all nodes have larger d[i]/u[i] than their parent
	- We can just ignore the tree requirement
*/

#include "job.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, nxt[mxN], ta[mxN];
vector<int> o;
ll u2[mxN], d2[mxN];

struct cmp {
	bool operator()(const int &a, const int &b) {
		return d2[a]*u2[b]>d2[b]*u2[a];
	}
};
priority_queue<int, vector<int>, cmp> c[mxN];

void dfs(int u) {
	o.push_back(u);
	for(; c[u].size(); c[u].pop())
		dfs(c[u].top());
}

ll scheduling_cost(vector<int> p, vector<int> u, vector<int> d) {
	n=p.size();
	memset(nxt, -1, 4*n);
	iota(ta, ta+n, 0);
	for(int i=n-1; ~i; --i) {
		u2[i]=u[i];
		d2[i]=d[i];
		while(c[i].size()) {
			int u=c[i].top();
			if(cmp()(u, i))
				break;
			c[i].pop();
			nxt[ta[i]]=u;
			ta[i]=ta[u];
			u2[i]+=u2[u];
			d2[i]+=d2[u];
			if(c[i].size()<c[u].size())
				swap(c[i], c[u]);
			for(; c[u].size(); c[u].pop())
				c[i].push(c[u].top());
		}
		if(i)
			c[p[i]].push(i);
	}
	dfs(0);
	sort(o.begin(), o.end(), cmp());
	ll t=0, ans=0;
	for(int i=o.size()-1; ~i; --i) {
		for(int j=o[i]; ~j; j=nxt[j]) {
			t+=d[j];
			ans+=t*u[j];
		}
	}
	return ans;
}
