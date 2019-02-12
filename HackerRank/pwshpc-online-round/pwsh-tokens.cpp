#include <bits/stdc++.h>
using namespace std;

template<size_t S>
struct linkcut {
	int p[S+1], pp[S+1], c[S+1][2], a[S+1], s[S+1], mn[S+1], mx[S+1];
	bool f[S+1];
	void cmb(int u) {
		s[u]=s[c[u][0]]+a[u]+s[c[u][1]];
		mn[u]=min(mn[c[u][0]], s[c[u][0]]+a[u]+mn[c[u][1]]);
		mx[u]=max(mx[c[u][0]], s[c[u][0]]+a[u]+mx[c[u][1]]);
	}
	int ci(int u) {
		return c[p[u]][1]==u;
	}
	void cn(int u, int v, int i) {
		if(u)
			p[u]=v;
		if(v)
			c[v][i]=u;
	}
	void ro(int u) {
		int v=p[u], w=p[v], i=ci(u), j=ci(v);
		cn(c[u][!i], v, i);
		cn(v, u, !i);
		cn(u, w, j);
		cmb(v);
		cmb(u);
		swap(pp[u], pp[v]);
	}
	int app(int u) {
		if(u) {
			f[u]^=1;
			swap(c[u][0], c[u][1]);
			swap(mn[u], mx[u]);
			mn[u]=s[u]-mn[u];
			mx[u]=s[u]-mx[u];
		}
		return u;
	}
	void psh(int u) {
		if(f[u]) {
			app(c[u][0]);
			app(c[u][1]);
			f[u]=0;
		}
	}
	void psha(int u) {
		if(!u)
			return;
		psha(p[u]);
		psh(u);
	}
	int spl(int u) {
		psha(u);
		while(p[p[u]]) {
			if(ci(u)==ci(p[u]))
				ro(p[u]);
			else
				ro(u);
			ro(u);
		}
		if(p[u])
			ro(u);
		return u;
	}
	void dc(int u, int i) {
		if(c[u][i]) {
			p[c[u][i]]=0;
			if(i)
				pp[c[u][i]]=u;
		}
		c[u][i]=0;
	}
	int xp(int u) {
		for(int v=0, w=u; w; v=w, w=pp[w]) {
			spl(w);
			dc(w, 1);
			cn(v, w, 1);
			pp[v]=0;
			cmb(w);
		}
		return spl(u);
	}
	int mr(int u) {
		return app(xp(u));
	}
	int bg(int u) {
		psh(u);
		return c[u][0]?bg(c[u][0]):spl(u);
	}
	int gr(int u) {
		return bg(xp(u));
	}
	bool lk(int u, int v) {
		if(mr(u)==gr(v))
			return 0;
		pp[mr(u)]=v;
		return 1;
	}
	bool ct(int u, int v) {
		if(mr(u)!=c[xp(v)][0]||c[u][1])
			return 0;
		dc(v, 0);
		cmb(v);
		return 1;
	}
};
linkcut<100000> lc;

int n, q;
string s, qt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q >> s;
	for(int i=0; i<n; ++i) {
		lc.a[i+1]=s[i]=='('?1:-1;
		lc.cmb(i+1);
	}
	for(int a, b; q--; ) {
		cin >> qt >> a;
		if(qt[0]=='c') {
			cin >> b;
			cout << (lc.lk(a, b)?"yes":"no") << "\n";
		} else if(qt[0]=='d') {
			cin >> b;
			cout << (lc.ct(a, b)?"yes":"no") << "\n";
		} else if(qt[0]=='t') {
			lc.spl(a);
			lc.a[a]*=-1;
			lc.cmb(a);
		} else {
			cin >> b;
			if(lc.gr(a)==lc.gr(b)) {
				lc.mr(a);
				lc.xp(b);
				cout << (lc.s[b]-2*lc.mn[b]?to_string(lc.s[b]-2*lc.mn[b]):"balanced") << "\n";
			} else
				cout << "invalid\n";
		}
	}
}
