/*
	- Find the shortest path between all ordered pairs with Floyd-Warshall
	- For each ordered pair (u, v), find the maximum profit by buying an item from u and selling it at v
	- Use the binary search trick to maximize the fraction	
		- For each ordered pair (u, v), make its edge weight profit-mid*length
		- We want to check if there exists a cycle that has a nonnegative weight, or negate all weights and use Floyd-Warshall
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=100, mxK=1000;
int n, m, k, b[mxN][mxK], s[mxN][mxK], a[mxN][mxN];
ll d1[mxN][mxN], d2[mxN][mxN];

void fw(ll d[mxN][mxN]) {
	for(int k=0; k<n; ++k)
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				d[i][j]=min(d[i][k]+d[k][j], d[i][j]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	for(int i=0; i<n; ++i)
		for(int j=0; j<k; ++j)
			cin >> b[i][j] >> s[i][j];
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int l=0; l<k; ++l)
				if(b[i][l]!=-1&&s[j][l]!=-1)
					a[i][j]=max(s[j][l]-b[i][l], a[i][j]);
	memset(d1, 0x3F, sizeof(d1));
	while(m--) {
		int v, w, t;
		cin >> v >> w >> t, --v, --w;
		d1[v][w]=t;
	}
	fw(d1);
	ll lb=1, rb=1e9;
	while(lb<=rb) {
		ll mb=(lb+rb)/2;
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				d2[i][j]=mb*min(d1[i][j], LLONG_MAX/2/mb)-a[i][j];
		fw(d2);
		bool ok=0;
		for(int i=0; i<n&&!ok; ++i)
			ok=d2[i][i]<=0;
		if(ok)
			lb=mb+1;
		else
			rb=mb-1;
	}
	cout << rb;
}
