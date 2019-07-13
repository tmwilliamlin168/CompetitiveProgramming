/*
	- For b=2, we can use the Manhattan distance to Chebyshev distance trick by rotating points by 45 degrees
	- Then we just have to query sum of points in rectangles, which can be done with sweepline + BIT
	- For b=3, the same trick applies, but the points become 4D
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int b, n, d, m;
long long ans;

namespace subtask2 {
	static const int MG1=1.5e5;
	array<int, 2> a[mxN];
	int ft[MG1];

	void upd(int i, int x) {
		for(++i; i<MG1; i+=i&-i)
			ft[i]+=x;
	}

	int qry(int i) {
		int r=0;
		for(; i; i-=i&-i)
			r+=ft[i];
		return r;
	}

	void solve() {
		for(int i=0; i<n; ++i) {
			cin >> a[i][0];
			if(b^1) {
				cin >> a[i][1];
				tie(a[i][0], a[i][1])=make_pair(a[i][0]+a[i][1], a[i][0]-a[i][1]-1+m);
			}
		}
		sort(a, a+n);
		for(int i=0, j=0; i<n; ++i) {
			while(a[j][0]<a[i][0]-d)
				upd(a[j++][1], -1);
			ans+=qry(min(a[i][1]+d+1, MG1-1))-qry(max(a[i][1]-d, 0));
			upd(a[i][1], 1);
		}
	}
}

namespace subtask3 {
	static const int MG1=223;
	array<int, 3> a[mxN];
	array<int, 4> b[mxN];
	int ft[MG1+1][MG1+1][MG1+1];

	void upd(int i1, int i2, int i3) {
		for(int j1=i1+1; j1<=MG1; j1+=j1&-j1)
			for(int j2=i2+1; j2<=MG1; j2+=j2&-j2)
				for(int j3=i3+1; j3<=MG1; j3+=j3&-j3)
					++ft[j1][j2][j3];
	}

	int qry(int i1, int i2, int i3) {
		int r=0;
		for(int j1=i1; j1; j1-=j1&-j1)
			for(int j2=i2; j2; j2-=j2&-j2)
				for(int j3=i3; j3; j3-=j3&-j3)
					r+=ft[j1][j2][j3];
		return r;
	}

	void solve() {
		for(int i=0; i<n; ++i) {
			cin >> a[i][0] >> a[i][1] >> a[i][2];
			b[i][0]=a[i][0]+a[i][1]+a[i][2]-3;
			b[i][1]=a[i][0]+a[i][1]-a[i][2]-2+m;
			b[i][2]=a[i][0]-a[i][1]+a[i][2]-2+m;
			b[i][3]=a[i][0]-a[i][1]-a[i][2]-1+2*m;
		}
		for(int i=0; i<MG1; ++i) {
			for(int j=0; j<n; ++j)
				if(b[j][3]==i)
					upd(b[j][0], b[j][1], b[j][2]);
			for(int j=0; j<n; ++j) {
				if(i^b[j][3]-d-1&&i^min(b[j][3]+d, MG1-1))
					continue;
				int l1=max(b[j][0]-d, 0), r1=min(b[j][0]+d+1, MG1), l2=max(b[j][1]-d, 0), r2=min(b[j][1]+d+1, MG1), l3=max(b[j][2]-d, 0), r3=min(b[j][2]+d+1, MG1);
				ans+=(i^b[j][3]-d-1?1:-1)*(qry(r1, r2, r3)-qry(r1, r2, l3)-qry(r1, l2, r3)+qry(r1, l2, l3)-qry(l1, r2, r3)+qry(l1, r2, l3)+qry(l1, l2, r3)-qry(l1, l2, l3));
			}
		}
		ans=(ans-n)/2;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> b >> n >> d >> m;
	if(b<3)
		subtask2::solve();
	else
		subtask3::solve();
	cout << ans;
}
