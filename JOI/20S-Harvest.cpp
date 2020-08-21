#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ll long long
#define ar array

const int mxN=2e5;
int n, m, a[mxN], b[mxN], nxt[mxN], f[mxN], q;
ll l, c, ans[mxN], l2, lz[mxN], s1[mxN];
vector<ar<ll, 2>> d[mxN];
bool vis[mxN], ic[mxN];
vector<int> cyc, adj[mxN];
oset<pair<ll, int>> *le[mxN];
vector<ll> lf[mxN], vx;

void dfs(int u) {
	vis[u]=1;
	for(int v : adj[u]) {
		if(ic[v])
			continue;
		dfs(v);
		lz[v]+=(a[v]-c%l+l-a[u]+l)%l+c;
		if(le[v]->size()>le[u]->size()) {
			swap(le[v], le[u]);
			swap(lz[v], lz[u]);
		}
		for(pair<ll, int> li : *le[v])
			le[u]->insert(make_pair(li.first+lz[v]-lz[u], li.second));
	}
	if(!ic[u])
		for(ar<ll, 2> di : d[u])
			ans[di[1]]=le[u]->order_of_key(make_pair(di[0]+1-lz[u], 0));
}

ll fd(ll a, ll b) {
	return a/b-(a%b<0);
}

ll fm(ll a, ll b) {
	ll c=a%b;
	return c<0?c+b:c;
}

int f1[mxN+1], ni;
ll f2[mxN+1];
oset<pair<ll, int>> f3[mxN+1];

void initds() {
	sort(vx.begin(), vx.end());
	memset(f1+1, 0, 4*vx.size());
	memset(f2+1, 0, 8*vx.size());
	for(int i=1; i<=vx.size(); ++i)
		f3[i].clear();
}

void ins(ll x) {
	int p=lower_bound(vx.begin(), vx.end(), x)-vx.begin();
	for(++p; p<=vx.size(); p+=p&-p) {
		++f1[p];
		f2[p]+=fd(x, l2);
		f3[p].insert(make_pair(fm(x, l2), ni++));
	}
}

ll qry(ll x) {
	int p=upper_bound(vx.begin(), vx.end(), x)-vx.begin();
	ll r=0;
	for(; p; p-=p&-p) {
		r+=fd(x, l2)*f1[p];
		r-=f2[p];
		r+=f3[p].order_of_key(make_pair(fm(x, l2)+1, 0));
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> l >> c;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<m; ++i)
		cin >> b[i];
	for(int i=0; i<n; ++i) {
		nxt[i]=upper_bound(a, a+n, a[i]-c%l)-a-1;
		if(nxt[i]<0)
			nxt[i]=upper_bound(a, a+n, a[i]-c%l+l)-a-1;
		adj[nxt[i]].push_back(i);
		le[i]=new oset<pair<ll, int>>();
	}
	for(int i=0; i<m; ++i) {
		f[i]=b[i]<a[0]?n-1:lower_bound(a, a+n, b[i])-a-1;
		le[f[i]]->insert(make_pair((b[i]-a[f[i]]+l)%l, i));
	}
	cin >> q;
	for(int i=0, v; i<q; ++i) {
		ll t;
		cin >> v >> t, --v;
		d[v].push_back({t, i});
	}
	for(int i=0; i<n; ++i) {
		if(vis[i])
			continue;
		int u=i;
		while(!vis[u]) {
			vis[u]=1;
			u=nxt[u];
		}
		l2=0;
		while(!ic[u]) {
			ic[u]=1;
			cyc.push_back(u);
			l2+=(a[u]-c%l+l-a[nxt[u]]+l)%l+c;
			u=nxt[u];
		}
		ll s1i=0;
		for(int ci : cyc) {
			dfs(ci);
			s1[ci]=s1i;
			for(pair<ll, int> li : *le[ci])
				lf[ci].push_back(li.first+lz[ci]);
			s1i+=(a[ci]-c%l+l-a[nxt[ci]]+l)%l+c;
			for(ll li : lf[ci])
				vx.push_back(li-s1[ci]);
		}
		initds();
		for(int ci : cyc) {
			for(ll li : lf[ci])
				ins(li-s1[ci]);
			for(ar<ll, 2> di : d[ci])
				ans[di[1]]+=qry(di[0]-s1[ci]);
		}
		vx.clear();
		reverse(cyc.begin(), cyc.end());
		s1i=-(a[cyc[0]]-c%l+l-a[nxt[cyc[0]]]+l)%l+c;
		for(int ci : cyc) {
			s1i+=(a[ci]-c%l+l-a[nxt[ci]]+l)%l+c;
			s1[ci]=s1i;
			for(ll li : lf[ci])
				vx.push_back(li+s1[ci]);
		}
		initds();
		for(int ci : cyc) {
			for(ar<ll, 2> di : d[ci])
				ans[di[1]]+=qry(di[0]-l2+s1[ci]);
			for(ll li : lf[ci])
				ins(li+s1[ci]);
		}
		vx.clear();
		cyc.clear();
	}
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}
