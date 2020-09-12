#include "fun.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> createFunTour(int n, int q) {
	vector<int> d(n), ans, e, g(n), f[3];
	array<int, 2> c{n+1};
	for(int i=0, s; i<n; ++i) {
		s=attractionsBehind(0, i);
		if(s>n/2)
			c=min(array<int, 2>{s, i}, c);
	}
	for(int i=0; i<n; ++i) {
		d[i]=hoursRequired(c[1], i);
		if(d[i]==1)
			e.push_back(i);
	}
	for(int i=0; i<n; ++i) {
		if(i==c[1])
			continue;
		while(g[i]<e.size()-1&&hoursRequired(e[g[i]], i)>d[i])
			++g[i];
		f[g[i]].push_back(i);
	}
	for(int i=0; i<e.size(); ++i) {
		sort(f[i].begin(), f[i].end(), [&](const int &i, const int &j) {
			return d[i]<d[j];
		});
	}
	int p[3]={0, 1, 2}, l=-1;
	while(1) {
		sort(p, p+3, [&](const int &i, const int &j) {
			return f[i].size()>f[j].size();
		});
		if(f[p[0]].size()<f[p[1]].size()+f[p[2]].size()) {
			sort(p, p+3, [&](const int &i, const int &j) {
				return d[f[i].back()]>d[f[j].back()];
			});
			int i=p[0]==l;
			ans.push_back(f[p[i]].back());
			f[p[i]].pop_back();
			l=p[i];
		} else
			break;
	}
	f[p[1]].insert(f[p[1]].end(), f[p[2]].begin(), f[p[2]].end());
	sort(f[p[1]].begin(), f[p[1]].end(), [&](const int &i, const int &j) {
		return d[i]<d[j];
	});
	l=ans.size()>1&&g[ans[ans.size()-2]]^p[0]&&d[ans[ans.size()-2]]>d[ans.back()]&&d[f[p[1]].back()]>d[ans.back()];
	for(; f[p[l]].size(); l^=1) {
		ans.push_back(f[p[l]].back());
		f[p[l]].pop_back();
	}
	ans.push_back(c[1]);
	return ans;
}
