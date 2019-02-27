/*
	- Do coordinate compression, and we end up with at most 200*200 important points
	- Check if edges can be added between adjacent points
	- We can use dijkstra to find a path that starts from v and goes around the main mansion
	- We only have to test 100 such v, which are the top-left corners of the rectangles
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int n, ax[2*mxN], ay[2*mxN], a, b, ans=1e9, d[8*mxN*mxN];
vector<int> xv, yv;
vector<array<int, 2>> adj[8*mxN*mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<2*n; ++i) {
		cin >> ax[i] >> ay[i];
		xv.push_back(ax[i]);
		yv.push_back(ay[i]);
	}
	sort(xv.begin(), xv.end());
	xv.resize(a=unique(xv.begin(), xv.end())-xv.begin());
	sort(yv.begin(), yv.end());
	yv.resize(b=unique(yv.begin(), yv.end())-yv.begin());
	auto bb=[&](int i1, int j1, int i2, int j2) {
		bool ok=1;
		for(int k=0; k<2*n&&ok; k+=2)
			ok=xv[i1]<=ax[k]&&xv[i2]<=ax[k]||xv[i1]>=ax[k+1]&&xv[i2]>=ax[k+1]||yv[j1]<=ay[k]&&yv[j2]<=ay[k]||yv[j1]>=ay[k+1]&&yv[j2]>=ay[k+1];
		if(ok) {
			for(int i=0; i<2; ++i, swap(i1, i2), swap(j1, j2))
				for(int j : {0, 1})
					adj[2*(i1*b+j1)+j].push_back({abs(xv[i1]-xv[i2])+abs(yv[j1]-yv[j2]), 2*(i2*b+j2)+(j^(yv[j1]<=ay[0]&&yv[j2]<=ay[0]&&(xv[i1]>ax[0])!=(xv[i2]>ax[0])))});
		}
	};
	for(int i=0; i<a; ++i) {
		for(int j=0; j<b; ++j) {
			if(i<a-1)
				bb(i, j, i+1, j);
			if(j<b-1)
				bb(i, j, i, j+1);
		}
	}
	auto gg=[&](int s, int t) {
		priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
		memset(d, 0x3f, sizeof(d));
		d[s]=0;
		pq.push({0, s});
		while(pq.size()) {
			array<int, 2> u=pq.top();
			pq.pop();
			if(d[u[1]]<u[0])
				continue;
			for(array<int, 2> v : adj[u[1]]) {
				if(d[v[1]]>u[0]+v[0]) {
					d[v[1]]=u[0]+v[0];
					pq.push({d[v[1]], v[1]});
				}
			}
		}
		ans=min(d[t], ans);
	};
	for(int i=0; i<a; ++i) {
		for(int j=0; j<b; ++j) {
			for(int k=0; k<2*n; k+=2) {
				if(xv[i]==ax[k]&&yv[j]==ay[k]) {
					gg(2*(i*b+j), 2*(i*b+j)+1);
					break;
				}
			}
		}
	}
	cout << ans;
}
