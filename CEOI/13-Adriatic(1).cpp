/*
	- The upper hull is the maximum set of points (xi, yi) such that for any other point (xj, yj), xj > xi or yj > yi, lower hull defined similarly
	- Shortest path from A -> B looks like A -> upper & lower hull points -> B
	- If d is the maximum distance from node u, the answer for node u is n*(d+1) - (# pts within dist d) - (# pts within dist d-1) - ... - (# pts withint dist 0)
	- Area covered for a certain distance looks like a cross, # pts inside can be calculated with prefix sums
	- Do something like bfs on the lower and upper hulls
		- Kind of fast as there are at most 5000 points on the lower and upper hulls altogether
		- Implement it to run in O(d) time
	- If some islands are close enough, the results are similar, using memoization allows the program to pass the TL
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2.5e5, mxC=2500;
int n, x[mxN], y[mxN], a[mxC][mxC], pa[mxC+1][mxC+1], uhbx[mxC+1], uhby[mxC+1], lhbx[mxC+1], lhby[mxC+1];

inline int spa(int x1, int y1, int x2, int y2) {
	return pa[x2][y2]-pa[x1][y2]-pa[x2][y1]+pa[x1][y1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> y[i], --x[i], --y[i];
		a[x[i]][y[i]]=i+1;
		pa[x[i]+1][y[i]+1]=1;
	}
	for(int i=1; i<=mxC; ++i) {
		for(int j=1; j<=mxC; ++j)
			pa[i][j]+=pa[i][j-1];
		for(int j=1; j<=mxC; ++j)
			pa[i][j]+=pa[i-1][j];
		uhbx[i]=uhbx[i-1];
		for(int j=uhbx[i]?y[uhbx[i]-1]-1:mxC-1; j>=0; --j)
			uhbx[i]=a[i-1][j]?a[i-1][j]:uhbx[i];
		uhby[i]=uhby[i-1];
		for(int j=uhby[i]?x[uhby[i]-1]-1:mxC-1; j>=0; --j)
			uhby[i]=a[j][i-1]?a[j][i-1]:uhby[i];
	}
	for(int i=mxC-1; i>=0; --i) {
		lhbx[i]=lhbx[i+1];
		for(int j=lhbx[i]?y[lhbx[i]-1]+1:0; j<mxC; ++j)
			lhbx[i]=a[i][j]?a[i][j]:lhbx[i];
		lhby[i]=lhby[i+1];
		for(int j=lhby[i]?x[lhby[i]-1]+1:0; j<mxC; ++j)
			lhby[i]=a[j][i]?a[j][i]:lhby[i];
	}
	map<pair<ll, ll>, int> hax1;
	for(int i=0; i<n; ++i) {
		int a1=pa[x[i]][y[i]], a2=spa(x[i]+1, y[i]+1, mxC, mxC), ans=-a1-a2-2, d=2, a3;
		if(a1+a2<n-1) {
			int uh1=uhbx[x[i]]-1, uh2=uhby[y[i]]-1, lh1=lhby[y[i]+1]-1, lh2=lhbx[x[i]+1]-1;
			if(!a1)
				uh1=uh2=i;
			if(!a2)
				lh1=lh2=i;
			ll hax2=(ll)uh1*mxN+uh2, hax3=(ll)lh1*mxN+lh2;
			if(hax1.find({hax2, hax3})==hax1.end()) {
				while(1) {
					++d;
					a3=pa[x[lh1]][y[lh2]]+spa(x[uh2]+1, y[uh1]+1, mxC, mxC)-spa(x[uh2]+1, y[uh1]+1, x[lh1], y[lh2]);
					ans-=a3;
					if(a3>=n)
						break;
					int nuh1=uhbx[x[lh1]]-1, nuh2=uhby[y[lh2]]-1;
					lh1=lhby[y[uh1]+1]-1, lh2=lhbx[x[uh2]+1]-1, uh1=nuh1, uh2=nuh2;
				}
				hax1[{hax2, hax3}]=ans+a1+a2+2+(d-2)*n;
			} else
				ans+=hax1[{hax2, hax3}];
		}
		cout << ans+d*n << "\n";
	}
}
