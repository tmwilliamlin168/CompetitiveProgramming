#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=100, bw=9;
int t, n, tba[mxN][mxN], qu[mxN], qh, qt, prv[mxN], d[mxN], d2[mxN], d3[mxN], p1=10, p2=3;
vector<array<int, 3>> ops;
vector<int> tbv[mxN];
priority_queue<array<int, 5>> pq;
array<int, 5> a2[mxN];

struct mgc1 {
	int a[mxN], s;
	bool b[mxN];
	vector<int> v;
	__attribute__((always_inline)) void add(int x) {
		if(!b[x]) {
			b[x]=1;
			v.push_back(x);
		}
		s+=!a[x];
		++a[x];
	}
	__attribute__((always_inline)) void rem(int x) {
		--a[x];
		s-=!a[x];
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
		s=0;
		memset(b, 0, n);
		v.clear();
	}
};

struct state {
	int ca, no, fo;
	mgc1 m1[mxN];
	void cf(state &o) {
		ca=o.ca;
		no=o.no;
		fo=o.fo;
		for(int i=0; i<n; ++i) {
			o.m1[i].uv();
			memcpy(m1[i].a, o.m1[i].a, 4*n);
			m1[i].s=o.m1[i].s;
			memcpy(m1[i].b, o.m1[i].b, n);
			m1[i].v=o.m1[i].v;
		}
	}
} sts[2][bw];

void bfs(state &st, int s, int t, int d[mxN]) {
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
		st.m1[u].it1(f1);
	}
}

int tv(state &st, int ta, int cb, bool pl) {
	if(cb>=0)
		st.m1[st.ca].rem(cb);
	bfs(st, st.ca, ta, d);
	if(prv[ta]==-1) {
		if(cb>=0)
			st.m1[st.ca].add(cb);
		return n;
	}
	if(!pl) {
		vector<pii> to;
		for(int i=ta; i!=st.ca; i=prv[i])
			to.push_back({i, cb});
		for(int i=(int)to.size()-1; i>=0; --i, ++st.no) {
			ops.push_back({to[i].fi, to[i].se, st.fo});
			st.fo=ops.size()-1;
		}
		st.ca=ta;
	}
	if(cb>=0)
		st.m1[st.ca].add(cb);
	return d[ta];
}

void solve() {
	cin >> n;
	sts[0][0].ca=0;
	sts[0][0].no=0;
	sts[0][0].fo=-1;
	int sb=0;
	for(int i=0; i<n; ++i) {
		int bi;
		cin >> bi;
		sb+=bi;
		for(int j=0; j<bi; ++j) { 
			int bij;
			cin >> bij, --bij;
			sts[0][0].m1[bij].add(i);
		}
		for(int j=0; j<bi; ++j) {
			int bij;
			cin >> bij, --bij;
			if(!tba[bij][i])
				tbv[i].push_back(bij);
			++tba[bij][i];
		}
	}
	int b=0, ns=1;
	if(sb<4.2*n) {
		for(int it=0; it<n; ++it) {
			bool ch=0;
			for(int si=0; si<ns; ++si) {
				bfs(sts[b][si], sts[b][si].ca, -1, d2);
				for(int i=0; i<n; ++i)
					a2[i]={INT_MAX, -1, -1, -1, -1};
				for(int i=0; i<n; ++i) {
					if(sts[b][si].m1[i].s<=2)
						continue;
					auto f1=[&](const int &j) {
						if(sts[b][si].m1[i].a[j]<=tba[i][j])
							return;
						ch=1;
						sts[b][si].m1[i].rem(j);
						bfs(sts[b][si], i, -1, d3);
						sts[b][si].m1[i].add(j);
						for(int k : tbv[j]) {
							if(sts[b][si].m1[k].s>=2||k==j)
								continue;
							if(d3[k]<n&&d2[i]+d3[k]<=p2)
								a2[k]=min(array<int, 5>{sts[b][si].no+d2[i]+d3[k], si, i, j, k}, a2[k]);
						}
					};
					sts[b][si].m1[i].it2(f1);
				}
				for(int i=0; i<n; ++i) {
					if(a2[i][1]!=-1) {
						pq.push(a2[i]);
						if(pq.size()>bw)
							pq.pop();
					}
				}
			}
			if(!ch||pq.empty())
				break;
			for(ns=0; !pq.empty(); ++ns) {
				array<int, 5> a=pq.top();
				pq.pop();
				sts[b^1][ns].cf(sts[b][a[1]]);
				tv(sts[b^1][ns], a[2], -1, 0);
				tv(sts[b^1][ns], a[4], a[3], 0);
			}
			b^=1;
		}
	}
	while(1) {
		bool ch=0;
		for(int si=0; si<ns; ++si) {
			bfs(sts[b][si], sts[b][si].ca, -1, d2);
			for(int i=0; i<n; ++i)
				a2[i]={INT_MAX, -1, -1, -1, -1};
			for(int i=0; i<n; ++i) {
				auto f1=[&](const int &j) {
					if(sts[b][si].m1[i].a[j]<=tba[i][j])
						return;
					ch=1;
					sts[b][si].m1[i].rem(j);
					bfs(sts[b][si], i, -1, d3);
					sts[b][si].m1[i].add(j);
					for(int k : tbv[j]) {
						if(sts[b][si].m1[k].a[j]>=tba[k][j])
							continue;
						if(d3[k]<n)
							a2[k]=min(array<int, 5>{sts[b][si].no+d2[i]+d3[k], si, i, j, k}, a2[k]);
					}
				};
				sts[b][si].m1[i].it2(f1);
			}
			for(int i=0; i<n; ++i) {
				if(a2[i][1]!=-1) {
					pq.push(a2[i]);
					if(pq.size()>bw)
						pq.pop();
				}
			}
		}
		if(!ch)
			break;
		if(pq.empty()) {
			cout << "-1\n";
			exit(0);
		}
		for(ns=0; !pq.empty(); ++ns) {
			array<int, 5> a=pq.top();
			pq.pop();
			sts[b^1][ns].cf(sts[b][a[1]]);
			tv(sts[b^1][ns], a[2], -1, 0);
			tv(sts[b^1][ns], a[4], a[3], 0);
		}
		b^=1;
	}
	vector<pii> to;
	for(int i=sts[b][ns-1].fo; i!=-1; i=ops[i][2])
		to.push_back({ops[i][0], ops[i][1]});
	cout << to.size() << "\n";
	for(int i=(int)to.size()-1; i>=0; --i)
		cout << to[i].fi+1 << " " << to[i].se+1 << "\n";
	for(int i=0; i<n; ++i) {
		sts[0][0].m1[i].clear();
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
