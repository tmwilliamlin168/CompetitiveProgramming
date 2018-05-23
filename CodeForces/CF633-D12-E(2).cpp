/*
	- Just a simpler (to code, not to understand) way to calculate p(l) than https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/CodeForces/CF633-D12-E(1).cpp
	- If c[l] <= v[l] then p(l) = c[l] (c[l] never increases)
	- Else, consider what happens to max(l, r) and min(l, r)
	- From l+1 => l, a prefix of max(l, r) becomes v[l] and a prefix of min(l, r) becomes c[l]
	- If the previous intersection point >= v[l] and <= c[l], then it is not the 2 prefixes and doesn't change
		- So the answer from p(l+1) is taken
	- If it was on a prefix then it either moves to v[l] or c[l]
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, k, v[mxN], c[mxN], p[mxN];
double ans, cp=1;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> v[i], v[i]*=100;
	for(int i=0; i<n; ++i)
		cin >> c[i];
	p[n-1]=min(v[n-1], c[n-1]);
	for(int i=n-2; i>=0; --i)
		p[i]=min(max(v[i], p[i+1]), c[i]);
	sort(p, p+n);
	for(int i=0; i<=n-k; cp=cp*(n-k-i)/(n-1-i), ++i)
		ans+=(double)p[i]*cp;
	cout << fixed << setprecision(9) << ans*k/n;
}
