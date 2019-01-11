#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, m, k, q, a[mxN], lng[mxN], r[mxN], p[mxN], qa, qb;
array<int, 3> es[mxN];
vector<array<int, 2>> adj[mxN];
array<int, 2> pe[mxN];

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

bool join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return 0;
	if(r[x]<r[y])
		swap(x, y);
	p[y]=x;
	r[x]+=r[x]==r[y];
	return 1;
}

template<typename T> struct ds {
	priority_queue<T, vector<T>, greater<T>> p1, p2;
	void add(T x) {
		p1.push(x);
	}
	void del(T x) {
		p2.push(x);
	}
	void dr() {
		while(p2.size()&&p1.top()==p2.top()) {
			p1.pop();
			p2.pop();
		}
	}
	T top() {
		dr();
		return p1.top();
	}
	void pop() {
		dr();
		p1.pop();
	}
};
ds<int> gg;
ds<array<int, 2>> ng[mxN];
unordered_map<int, ds<int>> mp[mxN];

void un(int u) {
	if(lng[u])
		gg.del(lng[u]);
	if(ng[u].top()[1]==a[u]) {
		array<int, 2> a=ng[u].top();
		ng[u].pop();
		lng[u]=ng[u].top()[0];
		ng[u].add(a);
	} else
		lng[u]=ng[u].top()[0];
	gg.add(lng[u]);
}

void dfs(int u=0, int p=-1) {
	for(array<int, 2> v : adj[u]) {
		if(v[0]==p) {
			pe[u]=v;
			continue;
		}
		if(mp[u].find(a[v[0]])==mp[u].end())
			mp[u][a[v[0]]].add(INT_MAX);
		mp[u][a[v[0]]].add(v[1]);
		dfs(v[0], u);
	}
	for(auto it=mp[u].begin(); it!=mp[u].end(); ++it)
		ng[u].add({it->second.top(), it->first});
	ng[u].add({INT_MAX, 0});
	un(u);
}

int main() {
	ifstream cin("grass.in");
	ofstream cout("grass.out");

	cin >> n >> m >> k >> q;
	for(int i=0; i<m; ++i)
		cin >> es[i][1] >> es[i][2] >> es[i][0], --es[i][1], --es[i][2];
	sort(es, es+m);
	iota(p, p+n, 0);
	for(int i=0; i<m; ++i) {
		if(join(es[i][1], es[i][2])) {
			adj[es[i][1]].push_back({es[i][2], es[i][0]});
			adj[es[i][2]].push_back({es[i][1], es[i][0]});
		}
	}
	for(int i=0; i<n; ++i)
		cin >> a[i];
	dfs();
	while(q--) {
		cin >> qa >> qb, --qa;
		if(qa) {
			int u=pe[qa][0];
			ng[u].del({mp[u][a[qa]].top(), a[qa]});
			mp[u][a[qa]].del(pe[qa][1]);
			ng[u].add({mp[u][a[qa]].top(), a[qa]});
			if(mp[u].find(qb)==mp[u].end())
				mp[u][qb].add(INT_MAX);
			else
				ng[u].del({mp[u][qb].top(), qb});
			mp[u][qb].add(pe[qa][1]);
			ng[u].add({mp[u][qb].top(), qb});
			un(u);
		}
		a[qa]=qb;
		un(qa);
		cout << gg.top() << "\n";
	}
}
