#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int t, n, k, c[mxN], cl[mxN], cr[mxN], d[17][mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	auto g=[](int l, int r) {
		int k=31-__builtin_clz(r-l+1);
		return max(d[k][l], d[k][r-(1<<k)+1]);
	};
	auto f=[&](int l, int m, int r, int x) {
		int lb1=l, rb1=m+1, lb2=m-1, rb2=r;
		while(lb1<rb1) {
			int mb=(lb1+rb1)/2;
			if(g(mb, m)>x)
				lb1=mb+1;
			else
				rb1=mb;
		}
		while(lb2<rb2) {
			int mb=(lb2+rb2+1)/2;
			if(g(m, mb)>x)
				rb2=mb-1;
			else
				lb2=mb;
		}
		return (long long)(m-lb1+1)*(lb2-m+1);
	};
	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> n >> k;
		for(int i=0; i<n; ++i) {
			cin >> c[i];
			cl[i]=i-1;
			while(cl[i]>=0&&c[cl[i]]<=c[i])
				cl[i]=cl[cl[i]];
		}
		for(int i=0; i<n; ++i)
			cin >> d[0][i];
		for(int i=1; i<17; ++i)
			for(int j=0; j+(1<<i)<=n; ++j)
				d[i][j]=max(d[i-1][j], d[i-1][j+(1<<i-1)]);
		long long ans=0;
		for(int i=n-1; ~i; --i) {
			cr[i]=i+1;
			while(cr[i]<n&&c[cr[i]]<c[i])
				cr[i]=cr[cr[i]];
			ans+=f(cl[i]+1, i, cr[i]-1, c[i]+k)-f(cl[i]+1, i, cr[i]-1, c[i]-k-1);
		}
		cout << "Case #" << ti << ": " << ans << "\n";
	}
}
