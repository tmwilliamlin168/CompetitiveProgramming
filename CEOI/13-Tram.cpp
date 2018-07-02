/*
	- The occupied seat with the minimum distance from a certain seat is on the nearest occupied row
	- Maintain for each pair of adjacent occupied rows the maximum distance if a person were to sit between those rows
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>
#define fi first
#define se second

const int mxN=1.5e5, mxM=3e4;
int n, m, p[mxM];
set<int> ors, av;
bool occ[mxN+1][2];

inline pli d2(int a) {
	int b=*ors.upper_bound(a);
	if(a==-1)
		return {(ll)b*b+(!occ[b][0]||!occ[b][1]), occ[b][0]&&!occ[b][1]};
	if(b==n)
		return {(ll)(n-1-a)*(n-1-a)+(!occ[a][0]||!occ[a][1]), 2*(n-1)+(occ[a][0]&&!occ[a][1])};
	ll d=b-a;
	if(d%2==0) {
		if(!(occ[a][0]&&occ[b][1])&&!(occ[a][1]&&occ[b][0]))
			return {(d/2)*(d/2)+1, 2*((a+b)/2)+occ[a][0]};
		return {(d/2)*(d/2), 2*((a+b)/2)};
	}
	int os=occ[a][0]+occ[a][1]+occ[b][0]+occ[b][1];
	if(os!=3)
		return {(d/2)*(d/2)+(os==2), 2*((a+b)/2)+(os==2&&occ[a][0])};
	return {(d/2)*(d/2)+1, 2*((a+b)/2+(occ[a][0]&&occ[a][1]))+(occ[a][0]&&occ[b][0])};
}

struct asicmp {
	inline bool operator()(const int &a, const int &b) const {
		ll da=d2(a).fi, db=d2(b).fi;
		return da==db?a<b:da>db;
	}
};
set<int, asicmp> asis;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	ors.insert(-1);
	ors.insert(n);
	for(int i=0; i<2*n; ++i)
		av.insert(i);
	asis.insert(-1);
	for(int mi=0; mi<m; ++mi) {
		char qt;
		cin >> qt;
		if(qt=='E') {
			p[mi]=*asis.begin();
			pli ad=d2(p[mi]);
			if(ad.fi<=1)
				p[mi]=*av.begin();
			else
				p[mi]=ad.se;
			av.erase(p[mi]);
			auto it=ors.lower_bound(p[mi]/2);
			asis.erase(*--it);
			asis.erase(p[mi]/2);
			occ[p[mi]/2][p[mi]%2]=1;
			ors.insert(p[mi]/2);
			asis.insert(*it);
			asis.insert(p[mi]/2);
			cout << p[mi]/2+1 << " " << p[mi]%2+1 << "\n";
		} else {
			int pk;
			cin >> pk, --pk;
			auto it=ors.lower_bound(p[pk]/2);
			asis.erase(*--it);
			asis.erase(p[pk]/2);
			occ[p[pk]/2][p[pk]%2]=0;
			if(occ[p[pk]/2][0]||occ[p[pk]/2][1])
				asis.insert(p[pk]/2);
			else
				ors.erase(p[pk]/2);
			asis.insert(*it);
			av.insert(p[pk]);
		}
	}
}
