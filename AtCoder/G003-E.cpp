/*
	- Consider the operations in reverse order
		- We start out with array of 1s, and we consider all i such that i >= q and we move them to a[i%q]
	- We can compress with array by storing differences
	- If we use a map and don't go through the elements i < q, each element will only be considered O(logq) times
		- If x >= y, x%y < x/2
	- O(qlogq+n)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int q;
ll a[100001];
map<ll, ll> mp;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> a[0] >> q;
	for(int i=1; i<=q; ++i)
		cin >> a[i];
	mp[a[q]]=1;
	for(int i=q-1; ~i; --i) {
		auto it=mp.end();
		while((--it)->first>a[i]) {
			mp[a[i]]+=it->first/a[i]*it->second;
			mp[it->first%a[i]]+=it->second;
			it=mp.erase(it);
		}
	}
	for(int i=a[0]; i; --i)
		mp[i-1]+=mp[i];
	for(int i=1; i<=a[0]; ++i)
		cout << mp[i] << "\n";
}
