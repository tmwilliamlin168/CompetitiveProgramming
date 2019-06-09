/*
	- View array as points on a plane
	- If we swap i < j, then a[i] > a[j]
	- Consider the rectangle with opposite endpoints (i, a[i]) and (j, a[j])
	- Total number of inversions saved is (number of points strictly within the rectangle) + (number of points within or on the rectangle) - 1
	- If x < y and a[x] >= a[y], then y will never be optimal as i
		- We can find a strictly increasing subset of candidates for i
	- We can prove that if i1 < i2, then optimal value of j for i1 < optimal value of j for i2
		- Divide and conquer, O(nlog^2n) total
	- Low constant, runs at comparable speeds to other segment tree O(nlogn) solutions
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[mxN], b[mxN], ft[mxN+1], a2;
long long ans;
vector<int> v;

void upd(int i, int x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]+=x;
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

void dc(int l1, int r1, int l2, int r2) {
	if(l1>r1) {
		for(int i=l2; i<=r2; ++i)
			upd(a[i], 1);
		return;
	}
	int m1=(l1+r1)/2;
	array<int, 2> m2{-1};
	for(int i=v[l1]; i<v[m1]; ++i)
		upd(a[i], -1);
	for(int i=l2; i<=r2; ++i) {
		upd(a[i], 1);
		m2=max(array<int, 2>{qry(a[v[m1]])+qry(a[v[m1]]+1)-qry(a[i])-qry(a[i]+1), i}, m2);
	}
	ans=min(1ll-m2[0], ans);
	for(int i=v[l1]; i<v[m1]; ++i)
		upd(a[i], 1);
	for(int i=l2; i<=r2; ++i)
		upd(a[i], -1);
	dc(l1, m1-1, l2, m2[1]);
	for(int i=v[m1]; i<v[m1+1]; ++i)
		upd(a[i], -1);
	upd(a[m2[1]], -1);
	dc(m1+1, r1, m2[1], r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	bool c=1, d=0;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		c&=!i||a[i]>=a[i-1];
		d|=i&&a[i]==a[i-1];
	}
	if(c) {
		cout << 1-d << "\n";
		return 0;
	}
	memcpy(b, a, 4*n);
	sort(b, b+n);
	for(int i=0; i<n; ++i) {
		a[i]=lower_bound(b, b+n, a[i])-b;
		if(!i||a[i]>a[v.back()])
			v.push_back(i);
	}
	v.push_back(n);
	dc(0, v.size()-2, 0, n-1);
	for(int i=n-1; ~i; --i) {
		ans+=qry(a[i]);
		upd(a[i], 1);
	}
	cout << ans << "\n";
}
