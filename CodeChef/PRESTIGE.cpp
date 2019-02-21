#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, m, rt=1, lc[mxN+1], rc[mxN+1], s0[mxN+1], a0[mxN+1], a1[mxN+1], qt, l1, r1, l2, r2, k, fp;
ll pr[mxN+1], s1[mxN+1], s2[mxN+1];
bool lz[mxN+1];

void app(int u) {
	lz[u]^=1;
	swap(a0[u], a1[u]);
	swap(s1[u], s2[u]);
	swap(lc[u], rc[u]);
}

void psh(int u) {
	if(!lz[u])
		return;
	if(lc[u])
		app(lc[u]);
	if(rc[u])
		app(rc[u]);
	lz[u]=0;
}

void rcl(int u) {
	s0[u]=1+s0[lc[u]]+s0[rc[u]];
	s1[u]=a0[u]+s1[lc[u]]+s1[rc[u]];
	s2[u]=a1[u]+s2[lc[u]]+s2[rc[u]];
}

int mrg(int u, int v) {
	if(!u||!v)
		return u^v;
	if(pr[u]>pr[v]) {
		psh(u);
		rc[u]=mrg(rc[u], v);
		rcl(u);
		return u;
	} else {
		psh(v);
		lc[v]=mrg(u, lc[v]);
		rcl(v);
		return v;
	}
}

array<int, 2> spl(int u, int k) {
	if(!u)
		return {0, 0};
	psh(u);
	if(k<=s0[lc[u]]) {
		array<int, 2> a=spl(lc[u], k);
		lc[u]=a[1];
		rcl(u);
		return {a[0], u};
	} else {
		array<int, 2> a=spl(rc[u], k-s0[lc[u]]-1);
		rc[u]=a[0];
		rcl(u);
		return {u, a[1]};
	}
}

void co(int l, int r, auto f) {
	array<int, 2> a=spl(rt, l-1), b=spl(a[1], r-l+1);
	f(b[0]);
	rt=mrg(a[0], mrg(b[0], b[1]));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=1; i<=n; ++i)
		cin >> a0[i];
	mt19937 mg(69);
	for(int i=1; i<=n; ++i) {
		cin >> a1[i];
		pr[i]=mg();
		rcl(i);
		if(i>1)
			rt=mrg(rt, i);
	}
	while(m--) {
		cin >> qt;
		if(qt==1) {
			cin >> l1 >> r1;
			co(l1, r1, [&](int u) {
				app(u);
			});
		} else if(qt==2) {
			cin >> k;
			fp=k-fp;
		} else {
			cin >> l1 >> r1 >> l2 >> r2;
			int m1=fp-l2+l1;
			ll ans=0;
			if(m1>=l1) {
				co(l1, min(m1, r1), [&](int u) {
					ans-=s1[u];
				});
			}
			if(m1<r1) {
				co(max(m1+1, l1), r1, [&](int u) {
					ans+=s1[u];
				});
			}
			cout << ans << "\n";
		}
	}
}
