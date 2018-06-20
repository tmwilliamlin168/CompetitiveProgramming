/*
	- dp(u, x) = cost to set the lengths of all paths from u's parent to the leaves in u's subtree to x
	- Convex and consists of line segments
	- Represented by y at x=0, y' at x=0, and a set of points where y' increases by 1
	- Merge all dp for u's children
		- Always merge small sets to large sets to achieve O(nlog^2n)
	- Modify dp(u) to take the wire from u's parent to u into account
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5;
int n, m, pi, c[mxN], si[mxN];
vector<int> adj[mxN];
ll yi0[mxN], yi1[mxN];
priority_queue<ll> pc[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=1; i<n+m; ++i) {
		cin >> pi >> c[i], --pi;
		adj[pi].push_back(i);
	}
	for(int i=n+m-1; i>=0; --i) {
		if(i>=n) {
			yi1[i]=-1;
			pc[i].push(0);
			pc[i].push(0);
			si[i]=i;
		} else {
			int mj=adj[i][0];
			for(int j : adj[i])
				if(pc[si[j]].size()<pc[si[j]].size())
					mj=j;
			si[i]=si[mj];
			for(int j : adj[i]) {
				yi0[i]+=yi0[j];
				yi1[i]+=yi1[j];
				if(j==mj)
					continue;
				while(!pc[si[j]].empty()) {
					pc[si[i]].push(pc[si[j]].top());
					pc[si[j]].pop();
				}
			}
		}
		while(pc[si[i]].size()>-yi1[i]+1)
			pc[si[i]].pop();
		ll a1=pc[si[i]].top();
		pc[si[i]].pop();
		ll a2=pc[si[i]].top();
		pc[si[i]].pop();
		pc[si[i]].push(a1+c[i]);
		pc[si[i]].push(a2+c[i]);
		yi0[i]+=c[i];
	}
	ll ans=yi0[0];
	pc[si[0]].pop();
	pc[si[0]].push(0);
	while(pc[si[0]].size()>1) {
		ans+=(yi1[0]+pc[si[0]].size()-2)*pc[si[0]].top();
		pc[si[0]].pop();
		ans-=(yi1[0]+pc[si[0]].size()-1)*pc[si[0]].top();
	}
	cout << ans;
}
