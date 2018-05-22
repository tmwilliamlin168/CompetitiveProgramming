#include <bits/stdc++.h>
using namespace std;

const int mxN1=1e5, mxN2=2e6;
int n, m, enc[256], ans[mxN1], ft[mxN2+1];
string ss[mxN1];
vector<int> pts[mxN2];

struct query {
	int i, l, r, w;
};
vector<query> queries[mxN2+1];

struct trie {
	int sz=1, c[mxN2][4], dt, st[mxN2], en[mxN2];
	inline void ins(string &s) {
		for(int i=0, u=0; i<s.size(); ++i) {
			if(!c[u][enc[s[i]]])
				c[u][enc[s[i]]]=sz++;
			u=c[u][enc[s[i]]];
		}
	}
	inline void dfs1(int u=0) {
		st[u]=dt++;
		for(int i=0; i<4; ++i)
			if(c[u][i])
				dfs1(c[u][i]);
		en[u]=dt;
	}
	inline int gi(string &s) {
		int u=0;
		for(int i=0; i<s.size(); u=c[u][enc[s[i]]], ++i)
			if(!c[u][enc[s[i]]])
				return -1;
		return u;
	}
} t[2];

inline void upd(int i, int x) {
	for(++i; i<=mxN2; i+=i&-i)
		ft[i]+=x;
}

inline int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	enc['A']=0;
	enc['G']=1;
	enc['C']=2;
	enc['U']=3;
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> ss[i];
		t[0].ins(ss[i]);
		reverse(ss[i].begin(), ss[i].end());
		t[1].ins(ss[i]);
	}
	t[0].dfs1();
	t[1].dfs1();
	for(int i=0; i<n; ++i) {
		int y=t[1].st[t[1].gi(ss[i])];
		reverse(ss[i].begin(), ss[i].end());
		int x=t[0].st[t[0].gi(ss[i])];
		pts[y].push_back(x);
	}
	for(int i=0; i<m; ++i) {
		string p, q;
		cin >> p >> q, reverse(q.begin(), q.end());
		int pi=t[0].gi(p), qi=t[1].gi(q);
		if(pi==-1||qi==-1)
			continue;
		queries[t[1].st[qi]].push_back({i, t[0].st[pi], t[0].en[pi], -1});
		queries[t[1].en[qi]].push_back({i, t[0].st[pi], t[0].en[pi], 1});
	}
	for(int i=0; i<mxN2; ++i) {
		for(int x : pts[i])
			upd(x, 1);
		for(query q : queries[i+1])
			ans[q.i]+=q.w*(qry(q.r)-qry(q.l));
	}
	for(int i=0; i<m; ++i)
		cout << ans[i] << "\n";
}
