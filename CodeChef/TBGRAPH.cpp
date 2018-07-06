/*
	- dp[i][j] = Maximum length of a path and how many ways to achieve it
	- Notice that dp[i][j] will only transition from dp[i+1][(j+1...k1)] and dp[(i+1...k2)][j+1] where k1 >= j and k2 >= i
		- Basically the places to transition from are the union of a segment of a row and a segment of a column
	- Also notice that the segments' endpoints are monotonic
		- Deque optimization
	- We just need to find k1 and k2 for each (i, j)
	- For each of the q rectangles, we can do max updates for O(log^2n) each
		- Set the k1 and k2 for each cell in the rectangle to the lower-right corner
		- If extra cells towards the right were set with k1, it wouldn't affect anything
			- Same if extra cells towards the bottom were set with k2
		- Updates can become 1D with O(logn) each, then apply prefix maximums
	- O(nm+q(logn+logm))
*/

#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int, int>
#define pil pair<int, ll>
#define fi first
#define se second
 
const int mxN=2000, M=1e9+7;
int n, m, q, qhr, qtr, qhc[mxN], qtc[mxN], mr[mxN][2*mxN], mc[mxN][2*mxN];
ll scr[mxN], scc[mxN][mxN];
pii qur[mxN], quc[mxN][mxN];
pil dp[mxN][mxN];

inline void qp1(pii *qu, int &qh, int &qt, ll *sc, int i, pil x) {
	sc[x.fi]+=x.se;
	while(qh<qt&&qu[qt-1].se<=x.fi)
		--qt;
	qu[qt++]={i, x.fi};
}

inline void qp2(pii *qu, int &qh, int &qt, ll *sc, int i, pil x) {
	sc[x.fi]-=x.se;
	if(qh<qt&&qu[qh].fi==i)
		++qh;
}

inline pil qq(pii *qu, int &qh, int &qt, ll *sc) {
	return qh<qt?pil(qu[qh].se, sc[qu[qh].se]):pil();
}

inline void stu(int *st, int n, int l, int r, int x) {
	for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
		if(l&1) {
			st[l]=max(x, st[l]);
			++l;
		}
		if(r&1) {
			st[r-1]=max(x, st[r-1]);
			--r;
		}
	}
}

inline void stpa(int *st, int n) {
	for(int i=2; i<2*n; ++i)
		st[i]=max(st[i/2], st[i]);
	memcpy(st, st+n, 4*n);
}

inline void cmb(pil &a, pil b) {
	++b.fi;
	if(b.fi>a.fi)
		a=b;
	else if(b.fi==a.fi)
		a.se+=b.se;
}

inline void solve() {
	cin >> n >> m >> q;
	while(q--) {
		int r1, c1, r2, c2;
		cin >> r1 >> c1 >> r2 >> c2, --r1, --c1, --r2, --c2;
		stu(mr[r1], m, c1, c2, r2);
		stu(mc[c1], n, r1, r2, c2);
	}
	for(int i=0; i<n; ++i) {
		stpa(mr[i], m);
		if(i)
			for(int j=0; j<m; ++j)
				mr[i][j]=max(max(mr[i-1][j], i), mr[i][j]);
	}
	for(int i=0; i<m; ++i) {
		stpa(mc[i], n);
		if(i)
			for(int j=0; j<n; ++j)
				mc[i][j]=max(max(mc[i-1][j], i), mc[i][j]);
	}
	int a1=1;
	memset(qhc, 0, 4*m);
	memset(qtc, 0, 4*m);
	for(int i=n-1; i>=0; --i) {
		qhr=qtr=0;
		for(int j=m-1; j>=0; --j) {
			dp[i][j]={1, 1};
			if(i>=n-1||j>=m-1)
				continue;
			qp1(qur, qhr, qtr, scr, j+1, dp[i+1][j+1]);
			for(int k=mc[j+1][i]; k>mc[j][i]; --k)
				qp2(qur, qhr, qtr, scr, k, dp[i+1][k]);
			cmb(dp[i][j], qq(qur, qhr, qtr, scr));
			qp1(quc[j], qhc[j], qtc[j], scc[j], i+1, dp[i+1][j+1]);
			for(int k=mr[i+1][j]; k>mr[i][j]; --k)
				qp2(quc[j], qhc[j], qtc[j], scc[j], k, dp[k][j+1]);
			cmb(dp[i][j], qq(quc[j], qhc[j], qtc[j], scc[j]));
			if(dp[i][j].fi==dp[i+1][j+1].fi+1)
				dp[i][j].se-=dp[i+1][j+1].se;
			dp[i][j].se%=M;
			a1=max(dp[i][j].fi, a1);
		}
		memset(scr, 0, 8*m);
	}
	for(int i=0; i<n; ++i)
		memset(mr[i], 0, 4*2*m);
	for(int i=0; i<m; ++i) {
		memset(mc[i], 0, 4*2*n);
		memset(scc[i], 0, 8*n);
	}
	ll a2=0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(dp[i][j].fi==a1)
				a2+=dp[i][j].se;
	cout << a1 << " " << a2%M << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while(t--)
		solve();
}
