/*
	- For each station i
		- Calculate the minimum cost to get to a station of level at least l[i]+1 on the left and right
		- For each j < sqrt(n), calculate the minimum cost to get to a station of level at least j*sqrt(n) on the left and right
	- Using the precalculated info, we can find the minimum cost to a station with at least an arbitrary level on the left and right in O(sqrt(n)) time
	- For each query (a, b)
		- Either the route goes through the maximum leveled station in [a, b]
		- Or the maximum leveled station in [a, b] is skipped by going through a2 < a and b2 > b such that the levels of stations a2 and b2 exceed all other levels in [a, b]
*/

#include <bits/stdc++.h>
using namespace std;

#define d1 array<int, 2>
#define d2 array<d1, 2>

const int mxN=1e5, BS=350;
int n, k, q, l[17][mxN], ln1[mxN], ln2[mxN], ld[mxN], rn1[mxN], rn2[mxN], rd[mxN];
d1 p[mxN];
d2 nxts[mxN], nxtb[(mxN-1)/BS+1][mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> k >> q;
	for(int i=0; i<n; ++i)
		cin >> l[0][i], --l[0][i];
	for(int i=1; i<17; ++i)
		for(int j=0; j<=n-(1<<i); ++j)
			l[i][j]=max(l[i-1][j], l[i-1][j+(1<<i-1)]);
	for(int i=0; i<n; ++i) {
		ln1[i]=ln2[i]=i-1;
		while(~ln1[i]&&l[0][ln1[i]]<=l[0][i])
			ln1[i]=ln1[ln1[i]];
		while(~ln2[i]&&l[0][ln2[i]]<l[0][i])
			ln2[i]=ln2[ln2[i]];
		if(~ln2[i])
			ld[i]=ld[ln2[i]]+1;
	}
	for(int i=n-1; ~i; --i) {
		rn1[i]=rn2[i]=i+1;
		while(rn1[i]<n&&l[0][rn1[i]]<=l[0][i])
			rn1[i]=rn1[rn1[i]];
		while(rn2[i]<n&&l[0][rn2[i]]<l[0][i])
			rn2[i]=rn2[rn2[i]];
		if(rn2[i]<n) {
			rd[i]=rd[rn2[i]]+1;
			nxts[i]={{{ld[i]-ld[ln1[i]], ln1[i]}, {rd[i]-rd[rn1[i]], rn1[i]}}};
		}
		p[i]={l[0][i], i};
	}
	sort(p, p+n);
	auto cmb=[](d2 a, d2 b, d2 c) {
		if(!b[1][0])
			b[1][0]=n;
		if(!c[0][0])
			c[0][0]=n;
		d2 r={min(d1{b[0][0]+a[0][0], b[0][1]}, d1{c[0][0]+a[1][0], c[0][1]}), min(d1{b[1][0]+a[0][0], b[1][1]}, d1{c[1][0]+a[1][0], c[1][1]})};
		r[0][0]=min(r[1][0]+1, r[0][0]);
		r[1][0]=min(r[0][0]+1, r[1][0]);
		return r;
	};
	auto qry=[&](int i, int t, int ex=0) {
		d2 r=nxtb[t/BS][i];
		for(int j=max(t/BS*BS, l[0][i]); j<t+ex; ++j) {
			int cl=r[0][1], cr=r[1][1];
			r=cmb(r, l[0][cl]>j?d2{{{0, cl}, {0, cl}}}:nxts[cl], l[0][cr]>j?d2{{{0, cr}, {0, cr}}}:nxts[cr]);
		}
		return r;
	};
	for(int i=0; i<k; i+=BS) {
		for(int j1=n-1; ~j1; --j1) {
			int j2=p[j1][1];
			nxtb[i/BS][j2]=l[0][j2]>=i?d2{{{0, j2}, {0, j2}}}:(nxtb[i/BS-1][j2][0][0]?cmb(nxtb[i/BS-1][j2], nxtb[i/BS][nxtb[i/BS-1][j2][0][1]], nxtb[i/BS][nxtb[i/BS-1][j2][1][1]]):qry(j2, i-1, 1));
		}
	}
	for(int a, b; q--; ) {
		cin >> a >> b, --a, --b;
		if(a>b)
			swap(a, b);
		int c=31-__builtin_clz(b-a+1), m=max(l[c][a], l[c][b-(1<<c)+1]);
		d2 da=qry(a, m), db=qry(b, m);
		int ans=da[1][0]+db[0][0]+ld[db[0][1]]-ld[da[1][1]];
		if(m+1<k) {
			da=qry(a, m+1), db=qry(b, m+1);
			ans=min(da[0][0]+db[1][0]+1, ans);
		}
		cout << ans-1 << "\n";
	}
}
