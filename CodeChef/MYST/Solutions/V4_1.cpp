#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=100;
int t, n, ca, tba[mxN][mxN], qu[mxN], qh, qt, prv[mxN], d[mxN], d2[mxN];
vector<pii> ops;
vector<int> tbv[mxN];

struct mgc1 {
	int a[mxN];
	bool b[mxN];
	vector<int> v;
	__attribute__((always_inline)) void add(int x) {
		if(!b[x]) {
			b[x]=1;
			v.push_back(x);
		}
		++a[x];
	}
	__attribute__((always_inline)) void rem(int x) {
		--a[x];
	}
	__attribute__((always_inline)) void uv() {
		int i2=0;
		for(int i1=0; i1<v.size(); ++i1) {
			if(!a[v[i1]]) {
				b[v[i1]]=0;
				continue;
			}
			v[i2++]=v[i1];
		}
		v.resize(i2);
	}
	__attribute__((always_inline)) void it1(auto f) {
		uv();
		for(int i : v)
			f(i);
	}
	__attribute__((always_inline)) void it2(auto f) {
		uv();
		vector<int> v2=v;
		for(int i : v2)
			f(i);
	}
	void clear() {
		memset(a, 0, 4*n);
		memset(b, 0, n);
		v.clear();
	}
} m1[mxN];

void bfs(int s, int t) {
	qh=qt=0;
	qu[qt++]=s;
	memset(prv, -1, 4*n);
	prv[s]=-2;
	memset(d, 0x3F, 4*n);
	d[s]=0;
	while(qh<qt&&(t==-1||prv[t]==-1)) {
		int u=qu[qh++];
		auto f1=[&](const int &v) {
			if(prv[v]==-1) {
				qu[qt++]=v;
				prv[v]=u;
				d[v]=d[u]+1;
			}
		};
		m1[u].it1(f1);
	}
}

int tv(int ta, int cb, bool pl) {
	if(ta==ca)
		return 1;
	if(cb>=0)
		m1[ca].rem(cb);
	bfs(ca, ta);
	if(prv[ta]==-1) {
		if(cb>=0)
			m1[ca].add(cb);
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
		m1[ca].add(cb);
	return d[ta];
}

void solve() {
	cin >> n;
	ca=0;
	for(int i=0; i<n; ++i) {
		int bi;
		cin >> bi;
		for(int j=0; j<bi; ++j) { 
			int bij;
			cin >> bij, --bij;
			m1[bij].add(i);
		}
		for(int j=0; j<bi; ++j) {
			int bij;
			cin >> bij, --bij;
			if(!tba[bij][i])
				tbv[i].push_back(bij);
			++tba[bij][i];
		}
	}
	while(1) {
		bool ch=0;
		bfs(ca, -1);
		memcpy(d2, d, 4*n);
		array<int, 4> a={2*n, -1, -1, -1};
		for(int i=0; i<n; ++i) {
			auto f1=[&](const int &j) {
				if(m1[i].a[j]<=tba[i][j])
					return;
				ch=1;
				for(int k : tbv[j]) {
					if(m1[k].a[j]>=tba[k][j])
						continue;
					int tca=ca;
					ca=i;
					a=min(array<int, 4>{d2[i]+tv(k, j, 1), i, j, k}, a);
					ca=tca;
				}
			};
			m1[i].it2(f1);
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
	cout << ops.size() << "\n";
	for(pii op : ops)
		cout << op.fi+1 << " " << op.se+1 << "\n";
	for(int i=0; i<n; ++i) {
		m1[i].clear();
		memset(tba[i], 0, 4*n);
		tbv[i].clear();
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
