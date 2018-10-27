/*
	- If a simple polygon encloses a point, any ray not parallel to any of the sides from that point must intersect the polygon an odd number of times
	- This becomes a graph problem
	- 4*n+8 nodes
		- 2*n+4 points in total and we need to duplicate points to keep track of the parity of the number of intersections with the ray
		- Each node is an ordered pair (point, even/odd intersections)
	- A bunch of cases to find the edges between the nodes
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=100, mxM=2*mxN+4, MG1=1000696969;
int n, s, a[mxM], b[mxM], m;
double d[2*mxM][2*mxM], ans=6969;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> s;
	for(int i=0; i<n; ++i)
		cin >> a[2*i] >> b[2*i] >> a[2*i+1] >> b[2*i+1];
	a[2*n]=a[2*n+1]=b[2*n]=b[2*n+3]=s;
	a[2*n+2]=a[2*n+3]=b[2*n+1]=b[2*n+2]=-s;
	m=2*n+4;
	for(int i=0; i<2*m; ++i)
		for(int j=0; j<2*m; ++j)
			d[i][j]=8*s;
	auto o1=[&](long long x1, long long y1, int x2, int y2) {
		return x1*y2==x2*y1?0:(x1*y2>x2*y1?1:-1);
	};
	auto il=[&](int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
		int a=o1(x2-x1, y2-y1, x3-x1, y3-y1), b=o1(x2-x1, y2-y1, x4-x1, y4-y1), c=o1(x4-x3, y4-y3, x1-x3, y1-y3), d=o1(x4-x3, y4-y3, x2-x3, y2-y3);
		return a&&b&&c&&d&&a!=b&&c!=d;
	};
	auto gc=[&](int x1, int y1, int x2, int y2) {
		return il(x1, y1, x2, y2, 0, 0, MG1, 1)?o1(x1, y1, MG1, 1):0;
	};
	auto aa=[&](int u, int v, double e, int c) {
		c&=1;
		d[u][v+c*m]=min(e, d[u][v+c*m]);
		d[v+c*m][u]=min(e, d[v+c*m][u]);
		d[u+m][v+(1-c)*m]=min(e, d[u+m][v+(1-c)*m]);
		d[v+(1-c)*m][u+m]=min(e, d[v+(1-c)*m][u+m]);
	};
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			if(il(a[2*i], b[2*i], a[2*i+1], b[2*i+1], a[2*j], b[2*j], a[2*j+1], b[2*j+1]))
				for(int k=0; k<4; ++k)
					aa(2*i+k%2, 2*j+k/2, 0, gc(a[2*i+k%2], b[2*i+k%2], a[2*j+k/2], b[2*j+k/2]));
	auto is=[&](long long x1, long long y1, int x2, int y2, int s, double &d) {
		for(int i=2*n; i<2*n+2; ++i)
			if(il(x1, y1, x2, y2, a[i]*s, b[i]*s, a[i+2]*s, b[i+2]*s))
				return;
		d=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/s;
	};
	for(int i=0; i<m; ++i) {
		for(int j=0; 2*j<m; ++j) {
			double d1=8*s;
			for(int k=2*j; k<2*j+2; ++k, d1=8*s) {
				is(a[i], b[i], a[k], b[k], 1, d1);
				if(d1<8*s)
					aa(i, k, d1, gc(a[i], b[i], a[k], b[k]));
			}
			if(j<n) {
				int bx=a[2*j+1]-a[2*j], by=b[2*j+1]-b[2*j], bm=bx*bx+by*by, adb=(a[i]-a[2*j])*bx+(b[i]-b[2*j])*by;
				if(0<=adb&&adb<=bm) {
					int cx=adb*bx+a[2*j]*bm, cy=adb*by+b[2*j]*bm;
					is(a[i]*bm, b[i]*bm, cx, cy, bm, d1);
					if(d1<8*s)
						for(int k=2*j; k<2*j+2; ++k)
							aa(i, k, d1, gc(a[i]*bm, b[i]*bm, cx, cy)+gc(cx, cy, a[k]*bm, b[k]*bm));
				}
			}
		}
	}
	for(int k=0; k<2*m; ++k)
		for(int i=0; i<2*m; ++i)
			for(int j=0; j<2*m; ++j)
				d[i][j]=min(d[i][k]+d[k][j], d[i][j]);
	for(int i=0; i<m; ++i)
		ans=min(d[i][i+m], ans);
	cout << fixed << setprecision(9) << ans;
}
