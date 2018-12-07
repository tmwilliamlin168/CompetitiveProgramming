#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int xm, ym, zm, n, m, k, ei, xl=mxN, xr, yl=mxN, yr, zl=mxN, zr, ea[mxN];
vector<int> ft[mxN+1], ftp[mxN+1];

struct event {
	int x1, x2, y1, y2, z, i, a;
	inline bool operator<(const event &o) const {
		return z==o.z?i<o.i:z<o.z;
	}
} es[3*mxN];

inline int qry(int x, int y) {
	int r=0;
	for(; x>0; x-=x&-x)
		for(int j=lower_bound(ftp[x].begin(), ftp[x].end(), y)-ftp[x].begin(); j>0; j-=j&-j)
			r+=ft[x][j];
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> xm >> ym >> zm >> n >> m >> k;
	for(int i=0; i<n; ++i) {
		int xi, yi, zi;
		cin >> xi >> yi >> zi, --xi, --yi, --zi;
		xl=min(xi, xl);
		xr=max(xi, xr);
		yl=min(yi, yl);
		yr=max(yi, yr);
		zl=min(zi, zl);
		zr=max(zi, zr);
	}
	for(int i=0; i<m; ++i) {
		cin >> es[i].x1 >> es[i].y1 >> es[i].z, --es[i].x1, --es[i].y1, --es[i].z;
		if(es[i].x1>=xl&&es[i].x1<=xr&&es[i].y1>=yl&&es[i].y1<=yr&&es[i].z>=zl&&es[i].z<=zr) {
			cout << "INCORRECT";
			return 0;
		}
		es[i].i=-1;
		for(int j=es[i].x1+1; j<=xm; j+=j&-j)
			ftp[j].push_back(es[i].y1);
	}
	cout << "CORRECT\n";
	for(int i=0; i<k; ++i) {
		int xi, yi, zi;
		cin >> xi >> yi >> zi, --xi, --yi, --zi;
		es[m+2*i]={min(xi, xl), max(xi, xr), min(yi, yl), max(yi, yr), min(zi, zl)-1, i, -1};
		es[m+2*i+1]={min(xi, xl), max(xi, xr), min(yi, yl), max(yi, yr), max(zi, zr), i, 1};
		if(xi>=xl&&xi<=xr&&yi>=yl&&yi<=yr&&zi>=zl&&zi<=zr)
			ea[i]=-1;
	}
	for(int i=1; i<=xm; ++i) {
		sort(ftp[i].begin(), ftp[i].end());
		ft[i]=vector<int>(ftp[i].size()+1);
	}
	sort(es, es+m+2*k);
	for(int ei=0; ei<m+2*k; ++ei) {
		if(es[ei].i!=-1)
			ea[es[ei].i]+=es[ei].a*(qry(es[ei].x2+1, es[ei].y2+1)-qry(es[ei].x1, es[ei].y2+1)-qry(es[ei].x2+1, es[ei].y1)+qry(es[ei].x1, es[ei].y1));
		else
			for(int j=es[ei].x1+1; j<=xm; j+=j&-j)
				for(int k=lower_bound(ftp[j].begin(), ftp[j].end(), es[ei].y1)-ftp[j].begin()+1; k<ft[j].size(); k+=k&-k)
					++ft[j][k];
	}
	for(int i=0; i<k; ++i)
		cout << (ea[i]==0?"UNKNOWN":(ea[i]<0?"OPEN":"CLOSED")) << "\n";
}
