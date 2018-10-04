#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll M=1e9+7;

struct Edge {
	int u, v;
	ll w;
	inline bool operator<(const Edge &o) const {
		return w<o.w;
	}
};

struct DSU {
	int *p, *r;
	DSU(int n) {
		p = new int[n];
		r = new int[n]();
		for(int i=0; i<n; ++i)
			p[i]=i;
	}
	int find(int x) {
		return x==p[x]?x:p[x]=find(p[x]);
	}
	inline bool join(int x, int y) {
		if((x=find(x))==(y=find(y)))
		   return 0;
		if(r[x]<r[y])
		   p[x]=y;
		else
		   p[y]=x;
		if(r[x]==r[y])
		   ++r[x];
		return 1;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	Edge *e = new Edge[m];
	for(int i=0; i<m; ++i) {
		int u, v, w;
		cin >> u >> v >> w, --u, --v;
		e[i]={u, v, w};
	}
	sort(e, e+m);
	DSU dsu(n);
	ll ans1=0, ans2=1;
	for(int i=0; i<m; ++i) {
		int j=i;
		while(i+1<m&&e[i+1].w==e[i].w)
			++i;
		set<pair<int, int>> us;
		int a=0, nm=0;
		for(int k=j; k<=i; ++k) {
			e[k].u=dsu.find(e[k].u), e[k].v=dsu.find(e[k].v);
			if(e[k].u>e[k].v)
				swap(e[k].u, e[k].v);
			if(e[k].u!=e[k].v) {
				us.insert({e[k].u, e[k].v});
				++a;
			}
		}
		for(int k=j; k<=i; ++k) {
			if(dsu.join(e[k].u, e[k].v)) {
				ans1+=e[k].w;
				++nm;
			}
		}
		if(a==3) {
			if(nm==1||nm==2&&us.size()==3)
				ans2=ans2*3%M;
			if(nm==2&&us.size()==2)
				ans2=ans2*2%M;
		} else if(a==2&&nm==1)
			ans2=ans2*2%M;
	}
	cout << ans1 << " " << ans2;
}
