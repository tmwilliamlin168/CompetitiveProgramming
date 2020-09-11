#include "towns.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=110;
int d[mxN][mxN], b[mxN], c[mxN];

int qry(int i, int j) {
	if(i^j&&!d[i][j])
		d[i][j]=d[j][i]=getDistance(i, j);
	return d[i][j];
}

int hubDistance(int n, int sub) {
	memset(d, 0, sizeof(d));
	array<int, 2> a{};
	for(int i=1; i<n; ++i)
		a=max(array<int, 2>{qry(0, i), i}, a);
	int di=0, ans=1e6, sl=0, sr=n;
	for(int i=0; i<n; ++i)
		di=max(qry(a[1], i), di);
	map<int, vector<int>> mp;
	for(int i=0, c; i<n; ++i) {
		b[i]=(qry(0, i)+qry(a[1], i)-qry(0, a[1]))/2;
		c=qry(a[1], i)-b[i];
		mp[c].push_back(i);
		ans=min(max(c, di-c), ans);
	}
	for(auto p : mp) {
		sr-=p.second.size();
		if(max(p.first, di-p.first)==ans&&sl<=n/2&&sr<=n/2) {
			vector<vector<int>> u, v;
			for(int i : p.second) {
				if(u.size()&&u.back().size()>v.back().size()) {
					if(qry(u.back()[0], i)<b[u.back()[0]]+b[i])
						u.back().push_back(i);
					else
						v.back().push_back(i);
				} else {
					u.push_back({i});
					v.push_back({});
				}
			}
			int m=u.back().size();
			for(int i=0; i<u.size()-1; ++i) {
				if(qry(u.back()[0], u[i][0])<b[u.back()[0]]+b[u[i][0]])
					m+=u[i].size();
				else
					for(int j : v[i])
						m+=qry(u.back()[0], j)<b[u.back()[0]]+b[j];
			}
			if(m<=n/2)
				ans=-ans;
		}
		sl+=p.second.size();
	}
	return -ans;
}
