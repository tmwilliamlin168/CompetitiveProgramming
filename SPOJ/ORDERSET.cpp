#include <bits/stdc++.h>
using namespace std;

template<size_t S>
struct splay {
	int n=1, rt, p[S+1], c[S+1][2], s[S+1], a[S+1];
	int nn(int x) {
		a[n]=x;
		s[n]=1;
		return n++;
	}
	void rcl(int u) {
		s[u]=s[c[u][0]]+1+s[c[u][1]];
	}
	int ir(int u) {
		return c[p[u]][1]==u;
	}
	void cn(int u, int v, int i) {
		if(u)
			p[u]=v;
		if(v)
			c[v][i]=u;
	}
	void ro(int u) {
		int v=p[u], w=p[v], i=ir(u), j=ir(v);
		cn(c[u][!i], v, i);
		cn(v, u, !i);
		cn(u, w, j);
		rcl(v);
		rcl(u);
	}
	int spl(int u) {
		while(p[p[u]]) {
			if(ir(u)==ir(p[u]))
				ro(p[u]);
			else
				ro(u);
			ro(u);
		}
		if(p[u])
			ro(u);
		return u;
	}
	int lb(int u, int x) {
		if(!u)
			return 0;
		int v=lb(c[u][a[u]<x], x);
		return v&&(a[u]<x||a[v]>=x)?v:u;
	}
	void ins(int x) {
		int u=lb(rt, x), v=nn(x);
		rt=spl(u);
		if(a[u]==x)
			return;
		cn(c[u][0], v, 0);
		c[u][0]=0;
		cn(u, v, 1);
		rcl(u);
		rcl(v);
		rt=v;
	}
	void del(int x) {
		int u=lb(rt, x);
		rt=spl(u);
		if(a[u]^x)
			return;
		if(c[u][0]) {
			cn(c[u][0], 0, 0);
			rt=spl(lb(c[u][0], x));
			cn(c[u][1], rt, 1);
			rcl(rt);
		} else {
			cn(c[u][1], 0, 1);
			rt=c[u][1];
		}
	}
	int kth(int k) {
		int u=rt;
		while(1) {
			if(k<s[c[u][0]])
				u=c[u][0];
			else if(k==s[c[u][0]]||!c[u][1])
				break;
			else {
				k-=s[c[u][0]]+1;
				u=c[u][1];
			}
		}
		rt=spl(u);
		return a[u];
	}
	int cntls(int x) {
		rt=spl(lb(rt, x));
		return s[c[rt][0]];
	}
};
splay<200001> spl;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	spl.rt=spl.nn(2e9);
	int q, x;
	cin >> q;
	for(char qt; q--; ) {
		cin >> qt >> x;
		if(qt=='I')
			spl.ins(x);
		else if(qt=='D')
			spl.del(x);
		else if(qt=='K')
			cout << (spl.kth(x-1)>1e9?"invalid":to_string(spl.kth(x-1))) << "\n";
		else
			cout << spl.cntls(x) << "\n";
	}
}
