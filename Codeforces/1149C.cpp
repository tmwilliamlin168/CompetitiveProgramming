#include <bits/stdc++.h>
using namespace std;

int n, q;
string s;

struct node {
	int ans, t1, p1, s1, t2, s2, t3, p3;
} st[1<<19];

void upd(int l1, int r1, int i=1, int l2=0, int r2=s.size()-1) {
	if(l2==r2) {
		st[i].ans=1;
		st[i].t1=1;
		st[i].p1=1;
		st[i].s1=1;
		st[i].t2=s[l2]==')'?1:-1;
		st[i].s2=s[l2]==')';
		st[i].t3=s[l2]=='('?1:-1;
		st[i].p3=s[l2]=='(';
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, r1, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, 2*i+1, m2+1, r2);
	st[i].ans=max({st[2*i].ans, st[2*i+1].ans, st[2*i].s2+st[2*i+1].p1, st[2*i].s1+st[2*i+1].p3});
	st[i].t1=max(st[2*i].t2+st[2*i+1].t1, st[2*i].t1+st[2*i+1].t3);
	st[i].p1=max({st[2*i].p1, st[2*i].t2+st[2*i+1].p1, st[2*i].t1+st[2*i+1].p3});
	st[i].s1=max({st[2*i+1].s1, st[2*i].s2+st[2*i+1].t1, st[2*i].s1+st[2*i+1].t3});
	st[i].t2=st[2*i].t2+st[2*i+1].t2;
	st[i].s2=max(st[2*i+1].s2, st[2*i].s2+st[2*i+1].t2);
	st[i].t3=st[2*i].t3+st[2*i+1].t3;
	st[i].p3=max(st[2*i].p3, st[2*i].t3+st[2*i+1].p3);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q >> s;
	upd(0, s.size()-1);
	cout << st[1].ans << "\n";
	for(int qi=0, ai, bi; qi<q; ++qi) {
		cin >> ai >> bi, --ai, --bi;
		swap(s[ai], s[bi]);
		upd(ai, ai);
		upd(bi, bi);
		cout << st[1].ans << "\n";
	}
}
