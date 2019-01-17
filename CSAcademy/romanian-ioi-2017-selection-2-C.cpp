#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, m, a[mxN], b[mxN], c[mxN], p[mxN], r[mxN], l[mxN], e[mxN], ev, bk[mxN];
vector<int> d[mxN+1];

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

void join(int x, int y) {
	x=find(x);
	bk[x]=bk[y];
	l[y]=l[x];
	if(r[x]<r[y])
		swap(x, y);
	p[y]=x;
	r[x]+=r[x]==r[y];
	e[x]+=e[y];
}

void dm(int i) {
	while(l[i=find(i)]&&(e[i]?e[i]>0:bk[find(l[i]-1)]>bk[i]))
		join(l[i]-1, i);
}

void ins(int i, array<int, 2> x) {
	r[i]=0;
	p[i]=l[i]=i;
	e[i]=x[0]-ev;
	ev=x[0];
	bk[i]=x[1];
	dm(i);
}

void upd(int x, int y) {
	e[find(x)]+=y;
	ev+=y;
	dm(x);
}

array<int, 2> chk(int mb) {
	ev=0;
	array<int, 2> ldp{mb, -1};
	for(int i=1; i<=mxN; ++i) {
		ins(i-1, ldp);
		for(int di : d[i])
			if(a[di]<i)
				upd(a[di], c[di]);
		ldp={e[find(0)]-mb, bk[find(0)]+1};
	}
	return ldp;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i] >> b[i] >> c[i], d[b[i]].push_back(i);
	int lb=0, rb=1e9;
	while(lb<rb) {
		int mb=(lb+rb)/2;
		array<int, 2> x=chk(mb);
		if(x[1]<=m)
			rb=mb;
		else
			lb=mb+1;
	}
	cout << chk(lb)[0]+m*lb;
}
