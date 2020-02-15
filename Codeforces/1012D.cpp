#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

string s, t;
vector<pii> a, b, ops;
bool sw;

inline void d(vector<pii> &v, pii p) {
	if(v.empty()||v.back().fi!=p.fi)
		v.push_back({p.fi, p.se});
	else
		v.back().se+=p.se;
}

inline void c(string &s, vector<pii> &v) {
	for(int i=s.size()-1; i>=0; --i)
		d(v, {s[i], 1});
}

inline void e(int s1) {
	int s2=0;
	pii pa=a.back();
	a.pop_back();
	for(int i=s1-1; i>=0; --i) {
		d(a, b[b.size()-i-1]);
		s2+=b[b.size()-i-1].se;
	}
	ops.push_back({pa.se, s2});
	for(int i=0; i<s1; ++i)
		b.pop_back();
	d(b, pa);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s >> t;
	c(s, a);
	c(t, b);
	if(a.size()>b.size()) {
		swap(a, b);
		sw=1;
	}
	if(a.back().fi==b.back().fi) {
		if((b.size()-a.size())%4==3)
			e((b.size()-a.size()+1)/2/2*2);
		int f=(b.size()-a.size())/2/2*2+1;
		a.push_back({b[b.size()-f-1].fi, 0});
		e(f);
	} else if(b.size()-a.size()>2)
		e((b.size()-a.size()+1)/2/2*2+1);
	while(a.size()>1||b.size()>1)
		e(1);
	cout << ops.size() << "\n";
	for(pii op : ops) {
		if(sw)
			swap(op.fi, op.se);
		cout << op.fi << " " << op.se << "\n";
	}
}
