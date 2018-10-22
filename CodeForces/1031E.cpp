#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxK=13, BS=6;
int n, a[mxN], qu[1<<mxK], qh, qt, d[1<<mxK], md;
vector<array<int, 3>> ops, otd[1<<BS];
vector<array<int, 4>> b, e;
array<int, 4> p[1<<mxK];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<BS; ++i) {
		for(int j=1; i+j<=BS; ++j) {
			array<int, 4> c={(1<<i|1<<(i+j)|1<<(i+2*j))&((1<<BS)-1), i, i+j, i+2*j};
			b.push_back(c);
			for(array<int, 4> c2 : b) {
				if(!otd[c[0]^c2[0]].size()) {
					otd[c[0]^c2[0]].push_back({c[1], c[2], c[3]});
					otd[c[0]^c2[0]].push_back({c2[1], c2[2], c2[3]});
				}
			}
		}
	}
	for(; n>mxK; n-=BS) {
		int m=0;
		for(int i=0; i<BS; ++i)
			m|=a[n-1-i]<<i;
		for(array<int, 3> op : otd[m]) {
			for(int i=0; i<3; ++i)
				a[n-1-op[i]]^=1;
			ops.push_back({n-1-op[2], n-1-op[1], n-1-op[0]});
		}
	}
	int k=min(n, mxK);
	for(int i=0; i<k; ++i)
		for(int j=1; i+2*j<k; ++j)
			e.push_back({1<<i|1<<(i+j)|1<<(i+2*j), i, i+j, i+2*j});
	memset(d, 1, sizeof(d));
	int s=0;
	for(int i=0; i<k; ++i)
		s|=a[i]<<i;
	d[s]=0;
	qu[qt++]=s;
	while(qh<qt) {
		int u=qu[qh++];
		md=max(d[u], md);
		for(array<int, 4> ei : e) {
			if(d[u]+1<d[u^ei[0]]) {
				d[u^ei[0]]=d[u]+1;
				p[u^ei[0]]=ei;
				qu[qt++]=u^ei[0];
			}
		}
	}
	if(d[0]>1e7) {
		cout << "NO";
		return 0;
	}
	for(int i=0; i!=s; i^=p[i][0])
		ops.push_back({p[i][1], p[i][2], p[i][3]});
	cout << "YES\n" << ops.size() << "\n";
	for(array<int, 3> op : ops)
		cout << op[0]+1 << " " << op[1]+1 << " " << op[2]+1 << "\n";
}
