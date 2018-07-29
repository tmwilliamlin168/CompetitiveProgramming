/*
	- https://codeforces.com/blog/entry/59650
*/

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int mxN=3e5, mxC=1e8;
int n, k, q, x[mxN+2], ts[2*mxN+1], e2i, st[2*(2*mxN+1)], ans[mxN];
vector<array<int, 2>> es1[mxN];
array<int, 3> qs[mxN];
array<int, 4> es2[4*mxN];

struct scmp {
	inline bool operator()(const int &a, const int &b) const {
		return x[a]==x[b]?a<b:x[a]<x[b];
	}
};
map<int, int, scmp> smp;

inline void solve() {
	for(int i=0; i<k; ++i) {
		smp[n+1]=0;
		for(auto a : es1[i]) {
			auto it1=smp.upper_bound(a[1]), it2=it1--;
			es2[e2i++]={(x[it1->fi]+x[it2->fi]+1)/2, x[it2->fi], it2->se, a[0]};
			it2->se=a[0];
			if(it1->fi==a[1]) {
				it2=it1--;
				es2[e2i++]={(x[it1->fi]+x[a[1]]+1)/2, x[a[1]], it2->se, a[0]};
				smp.erase(it2);
			} else
				smp[a[1]]=a[0];
		}
		es2[e2i++]={0, 2*mxC, smp[n+1], 2*n+1};
	}
	sort(es2, es2+e2i);
	for(int i1=0, i2=0; i1<q; ++i1) {
		while(i2<e2i&&es2[i2][0]<=qs[i1][0]) {
			for(int l=es2[i2][2]+2*n+1, r=es2[i2][3]+2*n+1; l<r; ++l/=2, r/=2) {
				if(l&1)
					st[l]=max(es2[i2][1], st[l]);
				if(r&1)
					st[r-1]=max(es2[i2][1], st[r-1]);
			}
			++i2;
		}
		for(int i=qs[i1][2]+2*n+1; i; i/=2)
			ans[qs[i1][1]]=max(st[i]-qs[i1][0], ans[qs[i1][1]]);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;
	for(int i=0; i<n; ++i) {
		int ti;
		cin >> x[i] >> ti >> ts[2*i] >> ts[2*i+1], --ti, ++ts[2*i+1];
		es1[ti].push_back({ts[2*i], i});
		es1[ti].push_back({ts[2*i+1], i});
	}
	x[n]=-2*mxC;
	x[n+1]=2*mxC;
	sort(ts, ts+2*n+1);
	for(int i=0; i<k; ++i) {
		for(auto &a : es1[i])
			a[0]=lower_bound(ts, ts+2*n+1, a[0])-ts;
		sort(es1[i].begin(), es1[i].end());
	}
	for(int i=0; i<q; ++i) {
		cin >> qs[i][0] >> qs[i][2], qs[i][2]=upper_bound(ts, ts+2*n+1, qs[i][2])-ts-1;
		qs[i][1]=i;
	}
	sort(qs, qs+q);
	smp[n]=0;
	solve();
	for(int i=0; i<n; ++i)
		x[i]=mxC-x[i];
	for(int i=0; i<q; ++i)
		qs[i][0]=mxC-qs[i][0];
	reverse(qs, qs+q);
	e2i=0;
	memset(st, 0, 4*2*(2*n+1));
	solve();
	for(int i=0; i<q; ++i)
		cout << (ans[i]>=mxC?-1:ans[i]) << "\n";
}
