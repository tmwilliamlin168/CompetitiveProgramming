#include "rect.h"
#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=2.5e3;
int n, m, l[mxN], r[mxN], ft[mxN+1];
vector<ar<int, 2>> p[mxN][mxN][2];
vector<int> d[mxN][mxN];

void upd(int i, int x) {
	for(++i; i<=m; i+=i&-i)
		ft[i]+=x;
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

void gr(vector<vector<int>> a, int b) {
	int n=a.size(), m=a[0].size();
	vector<ar<int, 3>> s;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			l[j]=j-1;
			while(~l[j]&&a[i][l[j]]<=a[i][j])
				l[j]=l[l[j]];
		}
		for(int j=m-1; ~j; --j) {
			r[j]=j+1;
			while(r[j]<m&&a[i][r[j]]<=a[i][j])
				r[j]=r[r[j]];
			if(~l[j]&&r[j]<m)
				d[l[j]+1][r[j]-1].push_back(i);
		}
	}
	for(int l1=0; l1<m; ++l1) {
		for(int r1=0; r1<m; ++r1) {
			for(int i=0, j; i<d[l1][r1].size(); i=j+1) {
				for(j=i; j+1<d[l1][r1].size()&&d[l1][r1][j+1]<=d[l1][r1][j]+1; ++j);
				int l2=d[l1][r1][i], r2=d[l1][r1][j], x2=r2, y2=r1;
				if(b)
					swap(x2, y2);
				for(int k=l2; k<=r2; ++k) {
					int x=k, y=l1;
					if(b)
						swap(x, y);
					p[x][y][b].push_back({-x2, y2});
				}
			}
			d[l1][r1].clear();
		}
	}
}

long long count_rectangles(vector<vector<int>> a) {
	n=a.size();
	m=a[0].size();
	vector<vector<int>> b(m, vector<int>(n));
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			b[j][i]=a[i][j];
	gr(a, 0);
	gr(b, 1);
	int ans=0;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			for(int k : {0, 1})
				sort(p[i][j][k].begin(), p[i][j][k].end());
			int d=0;
			for(int c=0; c<p[i][j][1].size(); ++c) {
				while(d<p[i][j][0].size()&&p[i][j][0][d]<=p[i][j][1][c])
					upd(p[i][j][0][d++][1], 1);
				ans+=qry(p[i][j][1][c][1]+1);
			}
			while(d)
				upd(p[i][j][0][--d][1], -1);
		}
	}
	return ans;
}
