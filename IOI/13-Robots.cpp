#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int mxN1=5e4, mxN2=1e6;
int a, b, t, x[mxN1], y[mxN1];
pair<int, int> ty[mxN2];
priority_queue<int> pq;

inline bool can(int m) {
	pq = priority_queue<int>();
	for(int i1=0, i2=0; i1<a; ++i1) {
		for(; i2<t&&ty[i2].fi<x[i1]; pq.push(ty[i2++].se));
		for(int j=0; j<m&&!pq.empty(); pq.pop(), ++j);
	}
	for(int i=t-1; i>=0&&ty[i].fi>=(a?x[a-1]:0); pq.push(ty[i--].se));
	for(int i1=b-1; i1>=0&&!(!pq.empty()&&pq.top()>=y[i1]); --i1)
		for(int j=0; j<m&&!pq.empty(); pq.pop(), ++j);
	return pq.empty();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> a >> b >> t;
	for(int i=0; i<a; ++i)
		cin >> x[i];
	sort(x, x+a);
	for(int i=0; i<b; ++i)
		cin >> y[i];
	sort(y, y+b);
	for(int i=0; i<t; ++i)
		cin >> ty[i].fi >> ty[i].se;
	sort(ty, ty+t);
	int l=1, r=t+1;
	while(l<=r) {
		int m=(l+r)/2;
		if(can(m))
			r=m-1;
		else
			l=m+1;
	}
	cout << (l>t?-1:l);
}
