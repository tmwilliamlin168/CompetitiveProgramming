#include <bits/stdc++.h>
using namespace std;

const int mxM=8e5;
int n, m, lc[mxM], rc[mxM], dt, rt, p[mxM], pr[mxM], sp[mxM], pe[mxM], pi;
string s;
char ci;

struct d1 {
	bool a, b;
	d1 operator+(const d1 &o) const {
		d1 r=o.a?d1{1, 0}:*this;
		r.b^=o.b;
		return r;
	}
	d1 operator+(const char &c) const {
		d1 r=*this;
		if((c!='&'||r.b)&&(c!='|'||!r.b))
			r={0, c=='^'&&r.b};
		return r;
	}
};

struct segtree {
	d1 a[1<<20];
	void upd(int l1, d1 x, int i=1, int l2=0, int r2=n-1) {
		if(l2==r2) {
			a[i]=x;
			return;
		}
		int m2=(l2+r2)/2;
		if(l1<=m2)
			upd(l1, x, 2*i, l2, m2);
		else
			upd(l1, x, 2*i+1, m2+1, r2);
		a[i]=a[2*i+1]+a[2*i];
	}
	d1 qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
		if(l1<=l2&&r2<=r1)
			return a[i];
		int m2=(l2+r2)/2;
		return (m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):d1{})+(l1<=m2?qry(l1, r1, 2*i, l2, m2):d1{});
	}
} st;

int dfs1(int &u) {
	if(s[dt]!='(') {
		u=dt++;
		lc[u]=rc[u]=-1;
		return 1;
	}
	dt++;
	int tlc, sl, sr;
	sl=dfs1(tlc);
	u=dt++;
	lc[u]=tlc;
	sr=dfs1(rc[u]);
	dt++;
	if(sl<sr)
		swap(lc[u], rc[u]);
	p[lc[u]]=p[rc[u]]=u;
	return sl+1+sr;
}

d1 dfs2(int u) {
	if(lc[u]==-1) {
		st.upd(sp[u], {1, s[u]-'0'});
		return {1, s[u]-'0'};
	}
	d1 ld=dfs2(lc[u]), rd=dfs2(rc[u])+s[u];
	st.upd(sp[u], rd);
	return ld+rd;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> s >> m;
	dfs1(rt);
	p[rt]=-1;
	for(int i=0; i<dt; ++i) {
		if(!p[i]||(p[i]!=-1&&i==lc[p[i]]))
			continue;
		for(int j=i; j!=-1; j=lc[j]) {
			pr[j]=i;
			sp[j]=n++;
			pe[i]=j;
		}
	}
	dfs2(rt);
	cout << st.qry(sp[rt], sp[pe[rt]]).b;
	while(m--) {
		cin >> pi >> ci, --pi;
		s[pi]=ci;
		d1 a=ci=='0'||ci=='1'?d1{}:st.qry(sp[rc[pi]], sp[pe[rc[pi]]]);
		while(pi!=-1) {
			if(s[pi]=='0'||s[pi]=='1')
				a={1, s[pi]-'0'};
			else
				a=a+s[pi];
			st.upd(sp[pi], a);
			a=st.qry(sp[pr[pi]], sp[pe[pr[pi]]]);
			pi=p[pr[pi]];
		}
		cout << a.b;
	}
}
