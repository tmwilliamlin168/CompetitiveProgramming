/*
	- If a segment with endpoints a and b uses a bridge at x, the cost is |x-a|+|x-b|
		- The optimal bridge for a set of segments is the median of the set of a and b's
	- For each segment, it is best to assign it to the bridge that is closest to its midpoint
	- Sort the segments by x+y
	- Partition into left and right parts, where each part has its own bridge
	- Calculate the answer for each prefix and suffix
		- Running median with 2 priority queues
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int k, n, med;
ll ba, a1[mxN+1], a2, bs, ts;
vector<pii> ps;
priority_queue<int> bpq;
priority_queue<int, vector<int>, greater<int>> tpq;

inline void upd(int x) {
	if(x<med)
		bpq.push(x), bs+=x;
	else
		tpq.push(x), ts+=x;
	if(bpq.size()+2<=tpq.size()) {
		bpq.push(med), bs+=med;
		med=tpq.top(), tpq.pop(), ts-=med;
	} else if(bpq.size()>=tpq.size()+2) {
		tpq.push(med), ts+=med;
		med=bpq.top(), bpq.pop(), bs-=med;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k >> n;
	for(int i=0; i<n; ++i) {
		char z1, z2;
		pii pi;
		cin >> z1 >> pi.fi >> z2 >> pi.se;
		if(z1!=z2) {
			ps.push_back(pi);
			++ba;
		} else
			ba+=abs(pi.fi-pi.se);
	}
	sort(ps.begin(), ps.end(), [](const pii &a, const pii &b) {
		return a.fi+a.se<b.fi+b.se;
	});
	for(int i=0; i<ps.size(); ++i) {
		upd(ps[i].fi), upd(ps[i].se);
		a1[i+1]=ts-(ll)tpq.size()*med+((ll)bpq.size()-1)*med-bs;
	}
	a2=a1[ps.size()];
	if(k==2) {
		bpq=priority_queue<int>(), tpq=priority_queue<int, vector<int>, greater<int>>();
		med=bs=ts=0;
		for(int i=ps.size()-1; i>0; --i) {
			upd(ps[i].fi), upd(ps[i].se);
			a2=min(a1[i]+ts-(ll)tpq.size()*med+((ll)bpq.size()-1)*med-bs, a2);
		}
	}
	cout << ba+a2;
}
