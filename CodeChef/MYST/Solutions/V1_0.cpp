#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=100;
int t, n, ca, ba[mxN][mxN], tba[mxN][mxN];
vector<pii> ops;
bool vis[mxN];

bool dfs(int u, int t, int cb) {
	if(u==t)
		return 1;
	vis[u]=1;
	if(cb>=0)
		--ba[u][cb];
	for(int v=0; v<n; ++v) {
		if(!ba[u][v]||vis[v])
			continue;
		ops.push_back({v, cb});
		if(cb>=0)
			++ba[v][cb];
		if(dfs(v, t, cb))
			return 1;
		ops.pop_back();
		if(cb>=0)
			--ba[v][cb];
	}
	if(cb>=0)
		++ba[u][cb];
	return 0;
}

inline bool tv(int ta, int cb) {
	memset(vis, 0, n);
	if(!dfs(ca, ta, cb))
		return 0;
	ca=ta;
	return 1;
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
	bool ch=1;
	while(ch) {
		ch=0;
		bool f=0;
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				if(ba[i][j]<=tba[i][j])
					continue;
				ch=1;
				int k=0;
				for(; k<n; ++k) {
					if(ba[k][j]>=tba[k][j])
						continue;
					int tos=ops.size(), tca=ca;
					if(tv(i, -1)&&tv(k, j))	
						break;
					while(ops.size()>tos)
						ops.pop_back();
					ca=tca;
				}
				if(k<n) {
					f=1;
					break;
				}
			}
		}
		if(ch&&!f) {
			cout << "-1\n";
			for(int i=0; i<n; ++i) {
				for(int j=0; j<n; ++j)
					cout << ba[i][j] << " ";
				cout << "\n";
			}
			exit(0);
		}
	}
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
