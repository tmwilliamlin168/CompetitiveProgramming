#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxM=5e5, mxQ=1e6;
int n, m, q, no;
vector<ar<int, 3>> v;

void pr(ar<int, 2> &a, int l, int t) {
	if(a[t^1]<=l&&a[t]<n-l)
		a[t]=n-l;
}

struct rmq {
	int n;
	vector<int> st;
	vector<int> rank;
	int mn(int a, int b) {
		if(b==-1)
			return a;
		return rank[a]<rank[b]?a:b;
	}
	void bld(vector<int> a, vector<int> rk) {
		rank=rk;
		n=a.size();
		st=vector<int>(2*n);
		for(int i=0; i<n; ++i)
			st[i+n]=a[i];
		for(int i=n-1; i; --i)
			st[i]=mn(st[2*i], st[2*i+1]);
	}
	int qry(int l, int r) {
		int b=-1;
		for(l+=n, r+=n+1; l<r; ++l/=2, r/=2) {
			if(l&1)
				b=mn(st[l], b);
			if(r&1)
				b=mn(st[r-1], b);
		}
		return b;
	}
};

struct node {
	vector<ar<int, 3>> q, qs;
	rmq rq;
	vector<vector<int>> pr;
	vector<int> p, rank;
	void dfs(int u) {
		for(int v : pr[u])
			dfs(v);
		p.push_back(u);
	}
	void bld() {
		int m=q.size();
		pr=vector<vector<int>>(m);
		set<ar<int, 3>> s;
		for(ar<int, 3> a : q) {
			auto it=s.lower_bound(a), it2=it;
			bool hp=0;
			if(it!=s.end()) {
				//type 1
				if(a[1]==1&&(*it)[1]==1) {
					pr[(*it)[2]].push_back(a[2]);
					hp=1;
				}
			}
			it=it2;
			if(it!=s.begin()) {
				--it;
				//type 0
				if(a[1]==0&&(*it)[1]==0) {
					pr[(*it)[2]].push_back(a[2]);
					hp=1;
				}
			}
			if(!hp)
				rank.push_back(a[2]);
			s.insert(a);
		}
		for(ar<int, 3> a : s)
			qs.push_back(a);
		for(int u : rank)
			dfs(u);
		rank=vector<int>(m);
		for(int i=0; i<m; ++i)
			rank[p[i]]=i;
		vector<int> sta;
		for(int i=0; i<m; ++i)
			sta.push_back(qs[i][2]);
		rq.bld(sta, rank);
		for(int i=0; i<m; ++i)
			vector<int>().swap(pr[i]);
		vector<vector<int>>().swap(pr);
		vector<int>().swap(sta);
		vector<int>().swap(rank);
	}
	void app(ar<int, 2> &a) {
		int l=lower_bound(qs.begin(), qs.end(), ar<int, 3>{a[0]})-qs.begin(), r=lower_bound(qs.begin(), qs.end(), ar<int, 3>{n-a[1]+1})-qs.begin()-1;
		if(l>r)
			return;
		int qi=rq.qry(l, r), p=lower_bound(qs.begin(), qs.end(), q[qi])-qs.begin();
		::pr(a, q[qi][1]?q[qi][0]:n-q[qi][0], q[qi][1]);
		if(q[qi][1]) {
			//vertical, then horizontal
			if(l>p-1)
				return;
			r=p-1;
		} else {
			//horizontal, then vertical
			if(p+1>r)
				return;
			l=p+1;
		}
		qi=rq.qry(l, r);
		::pr(a, q[qi][1]?q[qi][0]:n-q[qi][0], q[qi][1]);
	}
} st[1<<21];

void qry(ar<int, 2> &a, int l1, int r1, int i=1, int l2=0, int r2=(1<<20)-1) {
	if(l1<=l2&&r2<=r1) {
		st[i].app(a);
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		qry(a, l1, r1, 2*i, l2, m2);
	if(m2<r1)
		qry(a, l1, r1, 2*i+1, m2+1, r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	v=vector<ar<int, 3>>(m);
	for(int i=0; i<m; ++i)
		cin >> v[i][0] >> v[i][1];
	while(q--) {
		int qt;
		cin >> qt;
		if(qt==1) {
			int p;
			cin >> p, --p;
			ar<int, 2> a{v[p][0], v[p][1]};
			if(no)
				qry(a, v[p][2], no-1);
			cout << a[0] << " " << a[1] << "\n";
		} else if(qt==2||qt==3) {
			int l;
			cin >> l;
			for(int u=no+(1<<20); u; u/=2)
				st[u].q.push_back({qt&1?l:n-l, qt-2, st[u].q.size()});
			for(int u=no+(1<<20); ; u/=2) {
				st[u].bld();
				if((u+1)&1)
					break;
			}
			++no;
		} else if(qt==4) {
			int a, b;
			cin >> a >> b;
			v.push_back({a, b, no});
		}
	}
}
