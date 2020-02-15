#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4, mxK=10, mxL=100;
int n, k, l, xi, m, x[2*mxK], a[2*mxL], qu[mxN+1], d[mxN+1], c[2*mxK][2*mxK], dp[1<<(2*mxK)];
bool b[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> l;
	for(int i=0; i<k; ++i) {
		cin >> xi;
		b[xi]^=1;
		b[xi-1]^=1;
	}
	for(int i=0; i<=n; ++i)
		if(b[i])
			x[m++]=i;
	for(int i=0; i<l; ++i) {
		cin >> a[i];
		a[i+l]=-a[i];
	}
	for(int i=0; i<m; ++i) {
		int qt=0;
		qu[qt++]=x[i];
		memset(d, 1, 4*(n+1));
		d[x[i]]=0;
		for(int qh=0; qh<qt; ++qh) {
			int u=qu[qh];
			for(int j=0; j<2*l; ++j) {
				if(u+a[j]>=0&&u+a[j]<=n&&d[u+a[j]]>1e7) {
					qu[qt++]=u+a[j];
					d[u+a[j]]=d[u]+1;
				}
			}
		}
		for(int j=i+1; j<m; ++j)
			c[i][j]=d[x[j]];
	}
	memset(dp, 1, 4<<m);
	dp[0]=0;
	for(int i=3; i<1<<m; ++i)
		if(__builtin_popcount(i)&1^1)
			for(int j=0; j<m; ++j)
				if(i>>j&1)
					for(int k=j+1; k<m; ++k)
						if(i>>k&1)
							dp[i]=min(dp[i^1<<j^1<<k]+c[j][k], dp[i]);
	cout << (dp[(1<<m)-1]>1e7?-1:dp[(1<<m)-1]);
}
