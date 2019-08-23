/*
	- http://agc002.contest.atcoder.jp/data/agc/002/editorial.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	sort(a, a+n, greater<int>());
	int i=0;
	for(; i<n&&i<a[i]; ++i);
	cout << (a[i-1]-i+1&1&&lower_bound(a, a+n, i-1, greater<int>())-a-i+1&1?"Second":"First");
}
