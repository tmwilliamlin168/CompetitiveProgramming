#include <bits/stdc++.h>
using namespace std;

int n, k, m, ai, bi, INF=1e9, c[50], qt;

struct dat {
	int a;
	array<int, 2> l[50], r[50];
	dat() {
		for(int j=0; j<50; ++j) {
			l[j]={INF, j};
			r[j]={-INF, j};
		}
		a=INF;
	}
	dat(int i, int x) {
		new (this) dat();
		swap(l[x], l[0]);
		swap(r[x], r[0]);
		l[0][0]=r[0][0]=i;
		a=k==1?1:INF;
	}
	dat operator+(const dat &o) const {
		dat b;
		b.a=min(a, o.a);
		memset(c, 0, 4*k);
		int nc=k;
		for(int i1=k-1, i2=0; i1; --i1) {
			nc-=!c[r[i1][1]];
			--c[r[i1][1]];
			while(i2<k&&nc<k) {
				++c[o.l[i2][1]];
				nc+=!c[o.l[i2][1]];
				++i2;
			}
			if(nc<k)
				break;
			b.a=min(o.l[i2-1][0]-r[i1-1][0]+1, b.a);
		}
		memset(c, 0, 4*k);
		nc=0;
		for(int i=0; i<k; ++i) {
			if(l[i][0]>=INF)
				break;
			c[l[i][1]]=1;
			b.l[nc++]=l[i];
		}
		for(int i=0; i<k; ++i)
			if(!c[o.l[i][1]])
				b.l[nc++]=o.l[i];
		memset(c, 0, 4*k);
		nc=0;
		for(int i=0; i<k; ++i) {
			if(o.r[i][0]<=-INF)
				break;
			c[o.r[i][1]]=1;
			b.r[nc++]=o.r[i];
		}
		for(int i=0; i<k; ++i)
			if(!c[r[i][1]])
				b.r[nc++]=r[i];
		return b;
	}
} st[1<<18];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k >> m;
	for(int i=0; i<n; ++i)
		cin >> ai, --ai, st[(1<<17)+i]=dat(i, ai);
	for(int i=(1<<17)-1; i; --i)
		st[i]=st[2*i]+st[2*i+1];
	while(m--) {
		cin >> qt;
		if(qt==1) {
			cin >> ai >> bi, --ai, --bi;
			st[(1<<17)+ai]=dat(ai, bi);
			for(ai+=1<<17; ai/=2; )
				st[ai]=st[2*ai]+st[2*ai+1];
		} else
			cout << (st[1].a>n?-1:st[1].a) << "\n";
	}
}
