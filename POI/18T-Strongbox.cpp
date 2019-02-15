/*
	- If x is an opening position, then i*x is also an opening position
	- All opening positions can be described as 0, a, 2a, ..., where a is a factor of n
	- a will not be a factor of gcd(m[i], n) for i<k and is a factor of gcd(m[k], n)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, m, ans=1e18, p[12], n2;
int k, ps;
unordered_set<ll> v;

void dfs(ll u, bool ua=0) {
	if(ua)
		ans=min(u, ans);
	v.insert(u);
	for(int i=0; i<ps; ++i)
		if(u%p[i]==0&&v.find(u/p[i])==v.end())
			dfs(u/p[i], ua);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	n2=n;
	for(ll i=2; i*i<n; ++i) {
		if(n%i)
			continue;
		p[ps++]=i;
		while(n%i==0)
			n/=i;
	}
	if(n>0)
		p[ps++]=n;
	for(int i=0; i<k; ++i)
		cin >> m, dfs(__gcd(m, n2), i==k-1);
	cout << n2/ans;
}
