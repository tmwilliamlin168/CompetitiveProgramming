/*
	- Make the trees nodes and have edges with weight = space between two nodes
	- A path from, for example, top to bottom, will require the diameter of the person to be smaller than the maximum weight on the path
	- To find the maximum diameter to pass through, find a path such that the maximum weight is minimum
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>
#define fi first
#define se second

const int mxN=2e3, mxM=1e5;
int n, m;
ll w, h, x[mxN], y[mxN], r[mxN], sr[mxN][mxN], ans[4][4], dist[mxN];
bool vis[mxN];

ll c1(int a) {
	ll b=LLONG_MAX;
	memset(dist, 0x3F, 8*n);
	for(int i=0; i<n; ++i) {
		dist[i]=min(x[i]-r[i], dist[i]);
		dist[i]=min(h-y[i]-r[i], dist[i]);
		if(a==0)
			dist[i]=min(w-x[i]-r[i], dist[i]);
	}
	memset(vis, 0, n);
	for(int it=0; it<n; ++it) {
		int mi=-1;
		for(int i=0; i<n; ++i)
			if(!vis[i]&&(mi==-1||dist[i]<dist[mi]))
				mi=i;
		vis[mi]=1;
		for(int i=0; i<n; ++i)
			if(!vis[i])
				dist[i]=min(max(sr[i][mi], dist[mi]), dist[i]);
		b=min(max(y[mi]-r[mi], dist[mi]), b);
		if(a==1)
			b=min(max(w-x[mi]-r[mi], dist[mi]), b);
	}
	return b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> w >> h;
	for(int i=0; i<n; ++i)
		cin >> x[i] >> y[i] >> r[i];
	for(int i=0; i<n; ++i) {
		for(int j=i+1; j<n; ++j) {
			ll lb=1, rb=1e9;
			while(lb<=rb) {
				ll mb=(lb+rb)/2, a=mb+r[i]+r[j], dx=x[i]-x[j], dy=y[i]-y[j];
				if(a*a<=dx*dx+dy*dy)
					lb=mb+1;
				else
					rb=mb-1;
			}
			sr[i][j]=sr[j][i]=rb;
		}
	}
	for(int i=0, j=0, k=1; i<4; ++i, j^=2) {
		ans[i][i]=LLONG_MAX;
		ans[j][j^k]=ans[j^k][j]=c1(0);
		for(int l=0; l<n; ++l)
			y[l]=h-y[l];
		if(i==1) {
			ans[0][2]=ans[2][0]=c1(1);
			swap(w, h);
			for(int l=0; l<n; ++l)
				swap(x[l], y[l]);
			k^=2;
		} else if(i==0)
			ans[1][3]=ans[3][1]=c1(1);
	}
	while(m--) {
		int ri, ei;
		cin >> ri >> ei, --ei;
		for(int i=0; i<4; ++i)
			if(2*ri<=ans[ei][i])
				cout << i+1;
		cout << "\n";
	}
}
