#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e4, M=1e9+7;
const ll M2=(ll)M*M;
int t, n, l, k;
set<int> adj2[mxN];
vector<int> adj[mxN];
bool vis[mxN];

vector<ll> conv(vector<ll> a, vector<ll> b) {
	vector<ll> r(min((int)(a.size()+b.size())-1, k+1));
	for(int i=0; i<r.size(); ++i) {
		for(int j=max(i-(int)b.size()+1, 0); j<=min((int)a.size()-1, i); ++j) {
			r[i]+=a[j]*b[i-j];
			if(r[i]>=M2)
				r[i]-=M2;
		}
		r[i]%=M;
	}
	return r;
}

void dfs(int u, vector<int> &a) {
	vis[u]=1;
	a.push_back(u);
	for(int v : adj[u])
		if(!vis[v])
			dfs(v, a);
}

void ab(int u) {
	for(int v : adj[u])
		adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
}

void ar(int u) {
	for(int v : adj[u])
		adj[v].push_back(u);
}

vector<ll> rec(int rt);
vector<ll> pr(vector<int> v, int c) {
	vector<ll> a(c+1);
	a[c]=1;
	for(int vi : v)
		vis[vi]=0;
	int s=c;
	for(int vi : v) {
		if(vis[vi])
			continue;
		k-=s;
		vector<ll> r=rec(vi);
		k+=s;
		a=conv(a, r);
		while(s<a.size()&&!a[s])
			++s;
	}
	return a;
}

vector<ll> rec(int rt) {
	vector<int> a;
	dfs(rt, a);
	if(a.size()<2)
		return vector<ll>(k?2:1, 1);
	random_shuffle(a.begin(), a.end());
	int mu=a[0], ds=0;
	for(int ai : a) {
		if(adj[ai].size()>adj[mu].size())
			mu=ai;
		ds+=adj[ai].size();
	}
	if(ds>2*k*(int)adj[mu].size())
		return {0};
	ab(mu);
	vector<int> b=a;
	b.erase(find(b.begin(), b.end(), mu));
	vector<ll> a1=pr(b, 1);
	for(int v : adj[mu]) {
		b.erase(find(b.begin(), b.end(), v));
		ab(v);
	}
	vector<ll> a2=pr(b, adj[mu].size());
	for(int i=adj[mu].size()-1; ~i; --i)
		ar(adj[mu][i]);
	ar(mu);
	if(a1.size()<a2.size())
		swap(a1, a2);
	for(int i=0; i<a2.size(); ++i) {
		a1[i]+=a2[i];
		if(a1[i]>=M)
			a1[i]-=M;
	}
	return a1;
}

void solve() {
	cin >> n >> l >> k;
	for(int i=0; i<n; ++i)
		adj2[i].clear();
	for(int i=0, a, b; i<l; ++i) {
		cin >> a >> b, --a, --b;
		adj2[a].insert(b);
		adj2[b].insert(a);
	}
	priority_queue<array<int, 2>> pq;
	for(int i=0; i<n; ++i)
		pq.push({(int)adj2[i].size(), i});
	memset(vis, 0, n);
	while(~k) {
		array<int, 2> u=pq.top();
		pq.pop();
		if(u[0]<=k)
			break;
		if(u[0]>adj2[u[1]].size()) {
			pq.push({(int)adj2[u[1]].size(), u[1]});
			continue;
		}
		vis[u[1]]=1;
		for(int v : adj2[u[1]])
			adj2[v].erase(u[1]);
		adj2[u[1]].clear();
		--k;
	}
	for(int i=0; i<n; ++i)
		adj[i]=vector<int>(adj2[i].begin(), adj2[i].end());
	vector<int> v;
	for(int i=0; i<n; ++i)
		if(!vis[i])
			v.push_back(i);
	random_shuffle(v.begin(), v.end());
	vector<ll> ans=pr(v, 0);
	cout << accumulate(ans.begin(), ans.end(), 0ll)%M << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--)
		solve();
}
