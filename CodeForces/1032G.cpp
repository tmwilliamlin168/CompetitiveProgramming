#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, l[17][17][mxN], r[17][17][mxN];

array<int, 2> qry(int i, int l2, int r2) {
	int b=31-__builtin_clz(r2-l2+1);
	return {max(l[i][b][l2], l[i][b][(r2-(1<<b)+1)%n]-(r2-(1<<b)+1-l2)), max(r[i][b][(r2-(1<<b)+1)%n], r[i][b][l2]-(r2-(1<<b)+1-l2))};
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	if(n==1) {
		cout << 0;
		return 0;
	}
	for(int i=0; i<n; ++i)
		cin >> l[0][0][i], r[0][0][i]=l[0][0][i];
	for(int i=1; i<17; ++i) {
		int a=1<<(i-1);
		for(int j=0; j<n; ++j) {
			l[0][i][j]=max(l[0][i-1][j], l[0][i-1][(j+a)%n]-a);
			r[0][i][j]=max(r[0][i-1][(j+a)%n], r[0][i-1][j]-a);
		}
	}
	for(int i=1; i<17; ++i) {
		for(int j=0; j<17; ++j) {
			int a=1<<j;
			for(int k=0; k<n; ++k) {
				int l2=k-l[i-1][j][k], r2=k+a-1+r[i-1][j][k];
				if(r2-l2>=n-1) {
					l[i][j][k]=r[i][j][k]=n;
					continue;
				}
				if(l2<0) {
					l2+=n;
					r2+=n;
				}
				l[i][j][k]=l[i-1][j][k]+qry(i-1, l2, r2)[0];
				r[i][j][k]=r[i-1][j][k]+qry(i-1, l2, r2)[1];
			}
		}
	}
	for(int i=0; i<n; ++i) {
		int l2=i, r2=i, ans=1, l3, r3;
		for(int j=16; j>=0; --j) {
			l3=l2-qry(j, l2, r2)[0];
			r3=r2+qry(j, l2, r2)[1];
			if(r3-l3<n-1) {
				ans+=1<<j;
				l2=l3;
				r2=r3;
				if(l2<0) {
					l2+=n;
					r2+=n;
				}
			}
		}
		cout << ans << " ";
	}
}
