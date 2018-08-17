#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=100;
int t, n, ca, ba[mxN][mxN], tba[mxN][mxN], qu[mxN], qh, qt, prv[mxN], d[mxN], d2[mxN];
vector<pii> ops;

inline void bfs(int s, int t) {
	qh=qt=0;
	qu[qt++]=s;
	memset(prv, -1, 4*n);
	prv[s]=-2;
	memset(d, 0x3F, 4*n);
	d[s]=0;
	while(qh<qt&&(t==-1||prv[t]==-1)) {
		int u=qu[qh++];
		for(int v=0; v<n; ++v) {
			if(ba[u][v]&&prv[v]==-1) {
				qu[qt++]=v;
				prv[v]=u;
				d[v]=d[u]+1;
			}
		}
	}
}

inline int tv(int ta, int cb, bool pl) {
	if(cb>=0)
		--ba[ca][cb];
	bfs(ca, ta);
	if(prv[ta]==-1) {
		if(cb>=0)
			++ba[ca][cb];
		return n;
	}
	if(!pl) {
		vector<pii> to;
		for(int i=ta; i!=ca; i=prv[i])
			to.push_back({i, cb});
		for(int i=(int)to.size()-1; i>=0; --i)
			ops.push_back(to[i]);
		ca=ta;
	}
	if(cb>=0)
		++ba[ca][cb];
	return d[ta];
}

inline void solve() {
	cin >> n;
	ca=0;
	for(int i=0; i<n; ++i) {
		int bi;
		cin >> bi;
		for(int j=0; j<bi; ++j) { 
			int bij;
			cin >> bij, --bij;
			++ba[bij][i];
		}
		for(int j=0; j<bi; ++j) {
			int bij;
			cin >> bij, --bij;
			++tba[bij][i];
		}
	}
	while(1) {
		bool ch=0;
		bfs(ca, -1);
		memcpy(d2, d, 4*n);
		array<int, 4> a={n, -1, -1, -1};
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				if(ba[i][j]<=tba[i][j])
					continue;
				ch=1;
				for(int k=0; k<n; ++k) {
					if(ba[k][j]>=tba[k][j])
						continue;
					int tca=ca;
					ca=i;
					a=min(array<int, 4>{d2[i]+tv(k, j, 1), i, j, k}, a);
					ca=tca;
				}
			}
		}
		if(!ch)
			break;
		if(a[1]==-1) {
			cout << "-1\n";
			exit(0);
		}
		tv(a[1], -1, 0);
		tv(a[3], a[2], 0);
	}
//	int b=0, c=ops.size();
//	while(ops.size()<2*c) {
//		tv(b, -1, 0);
//		b^=1;
//	}
	cout << ops.size() << "\n";
	for(pii op : ops)
		cout << op.fi+1 << " " << op.se+1 << "\n";
	for(int i=0; i<n; ++i) {
		memset(ba[i], 0, 4*n);
		memset(tba[i], 0, 4*n);
	}
	ops.clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
