/*
	- For each pair of points, compute the vector and also the projection of the first point onto the vector
	- If 2 pairs have both of these same, then they can form a rectangle
	- Compute the minimum and maximum projection for all pairs that can form a rectangle
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1500;
int n;
ll x[mxN], y[mxN], ans;
pair<array<ll, 3>, ll> a[mxN*mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> x[i] >> y[i];
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			a[i*n+j]=make_pair(array<ll, 3>{x[j]-x[i], y[j]-y[i], (x[j]-x[i])*x[i]+(y[j]-y[i])*y[i]}, (y[i]-y[j])*x[i]+(x[j]-x[i])*y[i]);
	sort(a, a+n*n);
	for(int i=0, j=0; i<n*n; i=j)
		for(; j<n*n&&a[j].first==a[i].first; ++j)
			ans=max(a[j].second-a[i].second, ans);
	cout << ans;
}
