/*
	- Sort all people by c[i]-b[i]
	- There is an optimal solution where you can partition the people into 2 halves, B only appears on the left and C only appears on the right
	- Problem becomes 2 coins but for each prefix & suffix, done with priority queues
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int n, x, y, z;
pii ps[mxN];
long long a1, a2[mxN], a3[mxN+1], ans;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> x >> y >> z;
	n=x+y+z;
	for(int i=0; i<n; ++i) {
		int ai, bi, ci;
		cin >> ai >> bi >> ci;
		a1+=ai;
		ps[i]={bi-ai, ci-ai};
	}
	sort(ps, ps+n, [&](const pii &a, const pii &b) {
		return a.se-a.fi<b.se-b.fi;
	});
	for(int i=0; i<y; ++i) {
		a1+=ps[i].fi;
		pq.push(ps[i].fi);
	}
	a2[y]=0;
	for(int i=y; i<n-z; ++i) {
		a2[i+1]=a2[i];
		if(ps[i].fi>pq.top()) {
			a2[i+1]+=ps[i].fi-pq.top();
			pq.pop();
			pq.push(ps[i].fi);
		}
	}
	pq=priority_queue<int, vector<int>, greater<int>>();
	for(int i=n-1; i>=n-z; --i) {
		a1+=ps[i].se;
		pq.push(ps[i].se);
	}
	a3[n-z]=0;
	for(int i=n-z-1; i>=y; --i) {
		a3[i]=a3[i+1];
		if(ps[i].se>pq.top()) {
			a3[i]+=ps[i].se-pq.top();
			pq.pop();
			pq.push(ps[i].se);
		}
		ans=max(a1+a2[i]+a3[i], ans);
	}
	cout << max(a1+a2[n-z], ans);
}
