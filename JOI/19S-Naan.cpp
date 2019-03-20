#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e3;
int n, l, m, p[mxN], b[mxN];
ll v[mxN][mxN];
array<ll, 3> a[mxN][mxN+1], a1[mxN];

bool cmp(array<ll, 3> a, array<ll, 3> b) {
	return a[0]^b[0]?a[0]<b[0]:a[1]*b[2]<b[1]*a[2];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l;
	for(int i=0; i<n; ++i) {
		ll s=0, s2=0;
		for(int j=0; j<l; ++j)
			cin >> v[i][j], s+=v[i][j];
		a[i][0]={0, 0, 1};
		for(int j=0, k=1; j<l; ++j) {
			while(s2+n*v[i][j]>=s) {
				a[i][k++]={j, s-s2, n*v[i][j]};
				s2-=s;
			}
			s2+=n*v[i][j];
		}
		b[i]=n;
	}
	array<ll, 3> ls={l, 0, 1};
	for(int i=0; i<n; ++i) {
		int mi=-1;
		for(int j=0; j<n; ++j) {
			while(b[j]&&cmp(ls, a[j][b[j]]))
				--b[j];
			if(b[j]&&(mi==-1||cmp(a[mi][b[mi]-1], a[j][b[j]-1])))
				mi=j;
		}
		a1[i]=ls=a[mi][b[mi]-1];
		b[mi]=0;
		p[i]=mi;
	}
	for(int i=n-2; ~i; --i)
		cout << a1[i][0]*a1[i][2]+a1[i][1] << " " << a1[i][2] << "\n";
	for(int i=n-1; ~i; --i)
		cout << p[i]+1 << " ";
}
