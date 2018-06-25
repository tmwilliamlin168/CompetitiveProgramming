/*
	- For each update, update the answers to c=0...sqrt(n)
	- If c>sqrt(n), there are at most n/c=sqrt(n) teams that we need to consider
	- Fenwick tree for order statistics
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5, sqN=30;
int n, q, p[mxN], qt, qx, qy, ft[mxN+1];
ll s[mxN], ans[sqN];
set<pii> ps;

inline void upd(int i, int x) {
	for(; i<=n; i+=i&-i)
		ft[i]+=x;
}

inline int qry(int i) {
	int r=0;
	for(i=min(i, n); i>0; i-=i&-i)
		r+=ft[i];
	return r;
}

inline void rc(int x) {
	ps.erase({s[x], x});
	upd(s[x], -1);
	for(int i=1; i<sqN; ++i)
		ans[i]-=qry(s[x]+i-1)-qry(s[x]-i);
}

inline void ac(int x) {
	ps.insert({s[x], x});
	for(int i=1; i<sqN; ++i)
		ans[i]+=qry(s[x]+i-1)-qry(s[x]-i);
	upd(s[x], 1);
}

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

inline void join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return;
	if(s[x]<s[y])
		swap(x, y);
	p[y]=x;
	rc(x), rc(y);
	s[x]+=s[y];
	ac(x);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for(int i=0; i<n; ++i) {
		p[i]=i, s[i]=1;
		ac(i);
	}
	while(q--) {
		cin >> qt >> qx;
		if(qt==1) {
			cin >> qy, --qx, --qy;
			join(qx, qy);
		} else if(qx>=sqN) {
			ll a=0;
			auto it=ps.lower_bound({qx+1, 0});
			while(it!=ps.end()) {
				a+=qry(it->first-qx);
				++it;
			}
			cout << a << "\n";
		} else
			cout << (ll)ps.size()*(ps.size()-1)/2-ans[qx] << "\n";
	}
}
