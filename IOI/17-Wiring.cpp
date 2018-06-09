/*
	- A cluster of points with the same color can be split into left and right parts
		- The left part only connects to points on the left and the right part only connects to points on the right
		- Doesn't apply to clusters consisting of a single point
	- A point will only connect to a cluster next to it
	- dp[i] = minimum total length to connect first i points
	- The transition from dp[i] to dp[j] is basically just calculating subtask 2 as the range [j+1...i] will have parts of two clusters
	- Split into two cases according to whether the left part has more points than the right part
	- The rest is some math and transitions can be done efficiently with prefix minimums
*/

#include "wiring.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
const ll INF=1e18;
ll p[2*mxN], ps[2*mxN+1], dp[2*mxN+1], mn1[mxN+1]={INF};

ll min_total_length(vector<int> r, vector<int> b) {
	int n=r.size()+b.size();
	vector<pii> cls;
	for(int i=0, ri=0, bi=0, lc=-1, cc; i<n; ++i, lc=cc) {
		if(ri>=r.size()||bi<b.size()&&b[bi]<r[ri]) {
			p[i]=b[bi++];
			cc=0;
		} else {
			p[i]=r[ri++];
			cc=1;
		}
		ps[i+1]=p[i]+ps[i];
		if(cc!=lc)
			cls.push_back({i, i});
		else
			++cls.back().se;
	}
	for(int i=cls[0].fi; i<=cls[0].se; ++i)
		dp[i+1]=INF;
	for(int bi=0; bi<cls.size()-1; ++bi) {
		for(int i=0; i<=cls[bi].se-cls[bi].fi; ++i)
			mn1[i+1]=min(min(dp[i+cls[bi].fi], dp[cls[bi+1].fi])+(cls[bi].se-cls[bi].fi+1-i)*p[cls[bi+1].fi]+ps[cls[bi].fi+i], mn1[i]);
		ll mn2=INF;
		for(int i=0; i<=cls[bi+1].se-cls[bi+1].fi; ++i) {
			dp[i+cls[bi+1].fi+1]=mn2-(i+1)*p[cls[bi].se];
			if(i<=cls[bi].se-cls[bi].fi) {
				dp[i+cls[bi+1].fi+1]=min(mn1[cls[bi].se-cls[bi].fi+1-i]-(i+1)*p[cls[bi+1].fi], dp[i+cls[bi+1].fi+1]);
				mn2=min(min(dp[cls[bi].se-i], dp[cls[bi+1].fi])+(i+1)*p[cls[bi].se]+ps[cls[bi].se-i], mn2);
			}
			dp[i+cls[bi+1].fi+1]+=ps[cls[bi+1].fi+i+1]-2*ps[cls[bi+1].fi];
		}
	}
	return dp[n];
}
