/*
	- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest4_solutions/solutions.pdf
	- Any string chosen will have a period of n*m, so k will be at most n*m
*/

#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

const int mxN=500, di[8]={0, 1, 1, 1, 0, -1, -1, -1}, dj[8]={-1, -1, 0, 1, 1, 1, 0, -1}, B=29;
int n, m, k;
string g[mxN];
ull a1, a2, a3, c[2][mxN*mxN], e[2][mxN*mxN], f[8*mxN*mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k, k=min(n*m, k);
	for(int i=0; i<n; ++i)
		cin >> g[i];
	for(int d=0; d<8; ++d) {
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j)
				c[0][i*m+j]=g[i][j]-'a'+1;
		ull pB=B;
		memset(e[0], 0, 8*n*m);
		int a=0;
		for(int l=1; l<18; ++l, pB*=pB) {
			if(k>>l-1&1) {
				a^=1;
				for(int i=0; i<n; ++i)
					for(int j=0; j<m; ++j)
						e[a][i*m+j]=c[l&1^1][i*m+j]*pB+e[a^1][(i+(di[d]<<l-1)%n+n)%n*m+(j+(dj[d]<<l-1)%m+m)%m];
			}
			for(int i=0; i<n; ++i)
				for(int j=0; j<m; ++j)
					c[l&1][i*m+j]=c[l&1^1][i*m+j]*pB+c[l&1^1][(i+(di[d]<<l-1)%n+n)%n*m+(j+(dj[d]<<l-1)%m+m)%m];
		}
		memcpy(f+d*n*m, e[a], 8*n*m);
	}
	sort(f, f+8*n*m);
	for(int i=0, j=0; i<8*n*m; i=j) {
		for(; j<8*n*m&&f[j]==f[i]; ++j);
		a1+=1ll*(j-i)*(j-i);
	}
	a2=n*m*8, a2*=a2;
	a3=__gcd(a1, a2);
	cout << a1/a3 << "/" << a2/a3;
}
