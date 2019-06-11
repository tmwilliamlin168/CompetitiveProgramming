/*
	- Do a DP for the minimum distance from the destination to the right corners of the rectangles
	- Process from right to left, maintain a set of corners which have not been covered on the left by some rectangle
	- To transition for a new corner, just use the nearest corners in the set on the top and bottom
	- When recovering the path, changing the y coordinate before the x coordinate always works
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxA=1e6, mxM=2*mxN+3;
int n, m=2, x[mxM], y[mxM], c[mxM], p[mxM];
vector<array<int, 2>> ta[mxA+1], tr[mxA], ans;
set<array<int, 2>> s{{-mxA-1}, {mxA+1}};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> x[1] >> y[1] >> n;
	for(int i=0, x1, y1, x2, y2; i<n; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1>x2)
			swap(x1, x2);
		if(y1>y2)
			swap(y1, y2);
		ta[x2].push_back({y1, y2});
		tr[x1-1].push_back({y1, y2});
	}
	c[0]=1e9;
	auto cn=[](int xi, int yi) {
		x[m]=xi;
		y[m]=yi;
		set<array<int, 2>>::iterator it1=s.lower_bound({yi}), it2=--s.lower_bound({yi+1}), it;
		if(c[(*it1)[1]]+(*it1)[0]-yi<c[(*it2)[1]]+yi-(*it2)[0])
			it=it1;
		else
			it=it2;
		p[m]=(*it)[1];
		c[m]=c[p[m]]+abs(y[p[m]]-yi);
		if(c[m]<1e9)
			s.insert({yi, m++});
	};
	for(int i=mxA; ~i; --i) {
		if(i+1==x[1])
			s.insert({y[1], 1});
		for(array<int, 2> a : ta[i]) {
			cn(i+1, a[0]-1);
			cn(i+1, a[1]+1);
		}
		for(array<int, 2> a : ta[i]) {
			auto it=s.lower_bound({a[0]});
			while(it!=s.end()&&(*it)[0]<=a[1])
				it=s.erase(it);
			s.insert({a[0]});
		}
		for(array<int, 2> a : tr[i])
			s.erase({a[0]});
	}
	cn(0, 0);
	cout << c[m-1]+x[1] << "\n";
	for(int u=m-1; u>1; u=p[u]) {
		if(y[p[u]]^y[u]) {
			if(!ans.size()||ans.back()[0])
				ans.push_back({0, y[p[u]]-y[u]});
			else
				ans.back()[1]+=y[p[u]]-y[u];
		}
		if(x[p[u]]^x[u]) {
			if(!ans.size()||ans.back()[1])
				ans.push_back({x[p[u]]-x[u], 0});
			else
				ans.back()[0]+=x[p[u]]-x[u];
		}
	}
	cout << ans.size() << "\n";
	for(array<int, 2> a : ans)
		cout << a[0] << " " << a[1] << "\n";
}
