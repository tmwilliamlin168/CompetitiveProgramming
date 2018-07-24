#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2.5e5, M=1e9+7, B1=696969;
int n, m, q, sts=1, stv[mxN], p[mxN];
map<int, int> ch[mxN+1];
ll pb1[mxN/2+1];

struct stnode {
	int lc, rc, v;
	ll x1;
} st[2*mxN*19+1];

void upd(int &i, int l1, int x, int v, int l2=0, int r2=m-1) {
	if(st[i].v!=v) {
		st[sts]=st[i];
		i=sts++;
		st[i].v=v;
	}
	if(l2==r2) {
		st[i].x1=x;
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(st[i].lc, l1, x, v, l2, m2);
	else
		upd(st[i].rc, l1, x, v, m2+1, r2);
	st[i].x1=(st[st[i].lc].x1+pb1[m2-l2+1]*st[st[i].rc].x1)%M;
}

bool cmp(int i, int j, int l2=0, int r2=m-1) {
	if(l2==r2)
		return st[i].x1<st[j].x1;
	int m2=(l2+r2)/2;
	if(st[st[i].lc].x1==st[st[j].lc].x1)
		return cmp(st[i].rc, st[j].rc, m2+1, r2);
	return cmp(st[i].lc, st[j].lc, l2, m2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	pb1[0]=1;
	for(int i=1; i<=(n+1)/2; ++i)
		pb1[i]=pb1[i-1]*B1%M;
	while(q--) {
		int s, e, p, x;
		cin >> s >> e >> p >> x, --s, --p;
		ch[s][p]=x;
		if(ch[e].find(p)==ch[e].end())
			ch[e][p]=0;
	}
	for(int i=0; i<n; ++i) {
		p[i]=i;
		if(i)
			stv[i]=stv[i-1];
		for(auto it=ch[i].begin(); it!=ch[i].end(); ++it)
			upd(stv[i], it->first, it->second, i+1);
	}
	stable_sort(p, p+n, [&](const int &a, const int &b) {
		return cmp(stv[a], stv[b]);
	});
	for(int i=0; i<n; ++i)
		cout << p[i]+1 << "\n";
}
