#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5;
int n, m, li, ri, ans[mxN];
array<int, 2> h[mxN];
ll ph[mxN+1], xi;
bool act[mxN];
vector<array<ll, 4>> es;

struct dsu {
	int p[mxN], l[mxN], r[mxN];
	int find(int x) {
		return x==p[x]?x:(p[x]=find(p[x]));
	}
	void join(int x, int y) {
		if((x=find(x))==(y=find(y)))
			return;
		if(r[x]-l[x]<r[y]-l[y])
			swap(x, y);
		p[y]=x;
		l[x]=min(l[x], l[y]);
		r[x]=max(r[x], r[y]);
	}
	int gl(int x) {
		return l[find(x)];
	}
	int gr(int x) {
		return r[find(x)];
	}
} d;

struct segtree {
	int a[2*mxN];
	void upd(int i, int x) {
		for(a[i+=n]=x; i/=2; )
			a[i]=min(a[2*i], a[2*i+1]);
	}
	int qry(int l, int r) {
		int b=1e9;
		for(l+=n, r+=n; l<r; ++l/=2, r/=2) {
			if(l&1)
				b=min(a[l], b);
			if(r&1)
				b=min(a[r-1], b);
		}
		return b;
	}
} st;

ll gv(int l, int r) {
	return 2*(r+1-l)*(ph[r+1]-ph[l]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> h[i][0], ph[i+1]=ph[i]+h[i][0];
		h[i][1]=i;
		st.upd(i, -h[i][0]);
	}
	sort(h, h+n);
	for(int i=0; i<m; ++i) {
		cin >> li >> ri >> xi, --li, --ri;
		int lb=li, rb=ri+1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			if(gv(li, mb)>=xi)
				rb=mb;
			else
				lb=mb+1;
		}
		if(lb>ri) {
			ans[i]=-1;
			continue;
		}
		ans[i]=-st.qry(li, lb+1);
		lb=li, rb=ri;
		while(lb<rb) {
			int mb=(lb+rb+1)/2;
			if(gv(mb, ri)>=xi)
				lb=mb;
			else
				rb=mb-1;
		}
		ans[i]=min(-st.qry(lb, ri+1), ans[i]);
		es.push_back({xi, li, lb, i});
	}
	for(int i=0; i<n; ++i)
		d.p[i]=d.l[i]=d.r[i]=i;
	for(int i=0; i<n; ++i) {
		int j=h[i][1];
		act[j]=1;
		if(j&&act[j-1])
			d.join(j-1, j);
		if(j+1<n&&act[j+1])
			d.join(j, j+1);
		es.push_back({gv(d.gl(j), d.gr(j)), d.gl(j), h[i][0], -1});
	}
	sort(es.begin(), es.end(), [&](const array<ll, 4> &a, const array<ll, 4> &b) {
		return a[0]==b[0]?a[3]<b[3]:a[0]>b[0];
	});
	memset(st.a, 0x3f, 4*2*n);
	for(array<ll, 4> e : es) {
		if(e[3]==-1)
			st.upd(e[1], e[2]);
		else
			ans[e[3]]=min(st.qry(e[1], e[2]+1), ans[e[3]]);
	}
	for(int i=0; i<m; ++i)
		cout << ans[i] << "\n";
}
