/*
	- Any string chosen will have a period of n*m, so k will be at most n*m
	- For each of the 8 directions, we can decompose the grid into at most max(n, m) repeating strips
	- We can calculate the hashes in O(n*m) for each strip
	- Use of memcpy to barely pass TL
*/

#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

const int mxN=500, di[8]={0, 1, 1, 1, 0, -1, -1, -1}, dj[8]={-1, -1, 0, 1, 1, 1, 0, -1}, B=29;
int n, m, k;
string g[mxN];
bool vis[mxN][mxN];
ull h[2*mxN*mxN+1], a1, a2, a3, pB=1, c[8*mxN*mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k, k=min(n*m, k);
	for(int i=0; i<k; ++i)
		pB*=B;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	for(int d=0, e=0; d<8; ++d) {
		for(int i=0; i<n; ++i) {
			for(int j=0; j<m; ++j) {
				if(vis[i][j])
					continue;
				int a=0;
				for(int ci=i, cj=j; !vis[ci][cj]; ci=(ci+di[d]+n)%n, cj=(cj+dj[d]+m)%m) {
					vis[ci][cj]=1;
					h[++a]=g[ci][cj]-'a'+1;
				}
				for(int l=a; l+1<a+k; l+=a)
					memcpy(h+l+1, h+1, 8*a);
				for(int l=1; l<a+k; ++l)
					h[l]+=h[l-1]*B;
				for(int l=0; l<a; ++l)
					c[e++]=h[l+k]-h[l]*pB;
			}
		}
		memset(vis, 0, sizeof(vis));
	}
	sort(c, c+8*n*m);
	for(int i=0, j=0; i<8*n*m; i=j) {
		for(; j<8*n*m&&c[j]==c[i]; ++j);
		a1+=(ull)(j-i)*(j-i);
	}
	a2=n*m*8, a2*=a2;
	a3=__gcd(a1, a2);
	cout << a1/a3 << "/" << a2/a3;
}
