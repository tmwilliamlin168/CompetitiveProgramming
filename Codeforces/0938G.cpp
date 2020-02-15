/*
	- We can use dynamic connectivity for path xor queries
	- Let the length of a cycle be l
	- If we can get x as a path length from u to v, then we can travel from u to the cycle, traverse the cycle, go back to u, then to v and get a length of x^l
	- Becomes minimum subset xor problem
*/

#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=2e5;
int n, m, xi, yi, di, q, qt, r[mxN];
vector<ar<int, 3>> st[1<<19], ops;
map<ar<int, 2>, ar<int, 2>> mp;
ar<int, 2> qs[mxN], p[mxN];

struct dat {
	int a[31];
	void add(int x) {
		for(int i=0; x; ++i) {
			if(!a[i])
				a[i]=x;
			x=min(x^a[i], x);
		}
	}
	int qry(int x) {
		for(int i=0; a[i]; ++i)
			x=min(x^a[i], x);
		return x;
	}
};

ar<int, 2> find(int x) {
	if(x==p[x][0])
		return p[x];
	ar<int, 2> a=find(p[x][0]);
	return {a[0], a[1]^p[x][1]};
}

bool join(int x, int y, int w) {
	ar<int, 2> a=find(x), b=find(y);
	if((x=a[0])==(y=b[0]))
		return 0;
	w^=a[1]^b[1];
	if(r[x]<r[y])
		swap(x, y);
	ops.push_back({x, y, r[x]==r[y]});
	p[y]={x, w};
	r[x]+=r[x]==r[y];
}

void ae(int l1, int r1, ar<int, 3> x, int i=1, int l2=0, int r2=q-1) {
	if(l1>r1)
		return;
	if(l1<=l2&&r2<=r1) {
		st[i].push_back(x);
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		ae(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		ae(l1, r1, x, 2*i+1, m2+1, r2);
}

void solve(int i=1, int l2=0, int r2=q-1, dat d={}) {
	int t=ops.size();
	for(ar<int, 3> a : st[i]) {
		if(!join(a[0], a[1], a[2]))
			d.add(find(a[0])[1]^find(a[1])[1]^a[2]);
	}
	if(l2<r2) {
		int m2=(l2+r2)/2;
		solve(2*i, l2, m2, d);
		solve(2*i+1, m2+1, r2, d);
	} else if(qs[l2][0]^qs[l2][1])
		cout << d.qry(find(qs[l2][0])[1]^find(qs[l2][1])[1]) << "\n";
	while(ops.size()>t) {
		p[ops.back()[1]]={ops.back()[1], 0};
		r[ops.back()[0]]-=ops.back()[2];
		ops.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	while(m--) {
		cin >> xi >> yi >> di, --xi, --yi;
		mp[{xi, yi}]={di, 0};
	}
	cin >> q;
	for(int i=0; i<q; ++i) {
		cin >> qt >> xi >> yi, --xi, --yi;
		if(qt==1) {
			cin >> di;
			mp[{xi, yi}]={di, i};
		} else if(qt==2) {
			auto it=mp.find({xi, yi});
			ae(it->second[1], i, {xi, yi, it->second[0]});
			mp.erase(it);
		} else
			qs[i]={xi, yi};
	}
	for(auto it=mp.begin(); it!=mp.end(); ++it)
		ae(it->second[1], q-1, {it->first[0], it->first[1], it->second[0]});
	for(int i=0; i<n; ++i)
		p[i]={i};
	solve();
}
