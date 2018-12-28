/*
	- Write a slightly modified version FFT
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, m, q, a2;

vector<ll> solve(vector<int> a, ll p) {
	if(a.size()<=1)
		return {a[0]%m};
	vector<int> b1, b2;
	for(int i=0; i<a.size(); i+=2)
		b1.push_back(a[i]);
	for(int i=1; i<a.size(); i+=2)
		b2.push_back(a[i]);
	vector<ll> c1=solve(b1, p*p%m), c2=solve(b2, p*p%m), c(a.size());
	ll p1=p, p2=p;
	for(int i=0; i<a.size()/2; ++i, p2=p2*p%m);
	for(int i=0; i<a.size()/2; ++i, p1=p1*p%m, p2=p2*p%m) {
		c[i]=(c1[i]+p1*c2[i])%m;
		c[i+a.size()/2]=(c1[i]+p2*c2[i])%m;
	}
	return c;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> q;
	vector<int> a(n);
	for(int i=0; i<n; ++i)
		cin >> a[i];
	vector<ll> a1=solve(a, q);
	for(int i=0; i<n; ++i)
		a2=(a2+a1[i])%m;
	cout << a2 << "\n";
	for(int i=0; i<n; ++i)
		cout << a1[i] << " ";
}
