/*
	- Tips for mono-queue dp optimizations (wtever it's called) in general, not just for cht
	- When adding new candidate, check the top 2 candidates
		- Check if top candidate will be optimal at any time, if not, remove it
		- Top 1 will not be optimal if (maximum time of top 2 > top 1) > (maximum time of top 1 > current)
	- When querying, check the top 2 candidates and remove accordingly
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5, mxT=1e6;
int n, t, ft[mxT+1], ls, b[mxN+1], bs, st[mxN];
array<int, 2> a[mxN+2];
vector<int> bd[mxN+2], l[mxN+2], r[mxN+2], cl[mxN], cr[mxN];
vector<ll> dp[mxN+2];

int main() {
	ifstream cin("mowing.in");
	ofstream cout("mowing.out");
	
	cin >> n >> t;
	for(int i=1; i<=n; ++i)
		cin >> a[i][0] >> a[i][1];
	sort(a+1, a+n+1);
	a[n+1]={t, t};
	bd[0]={0};
	dp[0]={0};
	for(int i=1; i<=n+1; ++i) {
		ls=1;
		for(int j=a[i][1]; j; j-=j&-j)
			ls=max(ft[j]+1, ls);
		bd[ls].push_back(i);
		for(int j=a[i][1]; j<=t; j+=j&-j)
			ft[j]=max(ls, ft[j]);
		l[ls].push_back(l[ls].size()?l[ls].back():0);
		for(; a[bd[ls-1][l[ls].back()]][1]>a[i][1]; ++l[ls].back());
		r[ls].push_back(bd[ls-1].size());
	}
	for(int i=0; i<ls; ++i) {
		bs=1;
		for(int j=0; b[bs-1]<r[i+1].back(); ) {
			for(; j+1<l[i+1].size()&&l[i+1][j]<b[bs-1]; ++j);
			b[bs++]=r[i+1][j];
		}
		dp[i+1]=vector<ll>(l[i+1].size(), 1e18);
		for(int j=0; j<l[i+1].size(); ++j) {
			int p=upper_bound(b, b+bs, l[i+1][j])-b;
			cl[p-1].push_back(j);
			if(b[p]^r[i+1][j]) {
				cr[p].push_back(j);
			}
		}
		auto ev=[&](int k1, int k2) {
			return dp[i][k1]+(ll)(a[bd[i+1][k2]][0]-a[bd[i][k1]][0])*(a[bd[i+1][k2]][1]-a[bd[i][k1]][1]);
		};
		auto ot=[&](int k1, int k2) {
			int lb=0, rb=l[i+1].size();
			while(lb<rb) {
				int mb=(lb+rb)/2;
				if(ev(k1, mb)<ev(k2, mb))
					rb=mb;
				else
					lb=mb+1;
			}
			return lb;
		};
		for(int j=0; j+1<bs; ++j) {
			for(int k1=b[j+1]-1, k2=(int)cl[j].size()-1, sth=0; k1>=b[j]; --k1) {
				for(; sth>1&&ot(st[sth-1], st[sth-2])>ot(k1, st[sth-1]); --sth);
				st[sth++]=k1;
				for(; ~k2&&l[i+1][cl[j][k2]]>=k1; --k2) {
					for(; sth>1&&ev(st[sth-2], cl[j][k2])<ev(st[sth-1], cl[j][k2]); --sth);
					dp[i+1][cl[j][k2]]=min(ev(st[sth-1], cl[j][k2]), dp[i+1][cl[j][k2]]);
				}
			}
			for(int k1=b[j], k2=0, sth=0; k1<b[j+1]; ++k1) {
				for(; sth>1&&ot(st[sth-2], st[sth-1])<ot(st[sth-1], k1); --sth);
				st[sth++]=k1;
				for(; k2<cr[j].size()&&r[i+1][cr[j][k2]]<=k1+1; ++k2) {
					for(; sth>1&&ev(st[sth-2], cr[j][k2])<ev(st[sth-1], cr[j][k2]); --sth);
					dp[i+1][cr[j][k2]]=min(ev(st[sth-1], cr[j][k2]), dp[i+1][cr[j][k2]]);
				}
			}
		}
		for(int j=0; j+1<bs; ++j) {
			cl[j].clear();
			cr[j].clear();
		}
	}
	cout << dp[ls][0];
}
