/*
	- Problem is to find the MST and do https://codeforces.com/problemset/problem/915/F
	- https://www.topcoder.com/community/data-science/data-science-tutorials/line-sweep-algorithms/
	- Only 4 octants need to be checked
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int mxN=2.5e5;
int n, x[mxN], y[mxN], a[mxN], b[mxN], p[mxN], s[mxN], ei;
pii ft[mxN+1];
ll ans;

struct edge {
	int u, v, w;
	inline bool operator<(const edge &o) const {
		return w<o.w;
	}
} es[4*mxN];

inline void upd(int i, pii x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]=min(x, ft[i]);
}

inline pii qry(int i) {
	pii r={INT_MAX, -1};
	for(; i; i-=i&-i)
		r=min(ft[i], r);
	return r;
}

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

inline void join(int x, int y, ll w) {
	if((x=find(x))==(y=find(y)))
		return;
	if(s[x]>s[y])
		p[y]=x;
	else
		p[x]=y;
	ans+=w*s[x]*s[y];
	s[x]=s[y]=s[x]+s[y];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> y[i];
		a[i]=p[i]=i;
		s[i]=1;
	}
	for(int d=0; d<4; ++d) {
		for(int i=0; i<n; ++i) {
			if(d==1||d==3)
				x[i]=-x[i];
			else if(d==2)
				swap(x[i], y[i]);
			b[i]=x[i]-y[i];
		}
		sort(a, a+n, [&](const int &i, const int &j) {
			return x[i]==x[j]?y[i]>y[j]:x[i]>x[j];
		});
		sort(b, b+n);
		for(int i=1; i<=n; ++i)
			ft[i]={INT_MAX, -1};
		for(int i=0; i<n; ++i) {
			int j=lower_bound(b, b+n, x[a[i]]-y[a[i]])-b, k=qry(j+1).second;
			if(k!=-1)
				es[ei++]={a[i], k, x[k]-x[a[i]]+y[k]-y[a[i]]};
			upd(j, {x[a[i]]+y[a[i]], a[i]});
		}
	}
	sort(es, es+ei);
	for(int i=0; i<ei; ++i)
		join(es[i].u, es[i].v, es[i].w/2);
	cout << ans;
}
