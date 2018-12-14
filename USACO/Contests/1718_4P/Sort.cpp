#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, ft[mxN+1];
array<int, 2> a[mxN], b[mxN];
long long ans=0;

void upd(int i) {
	for(++i; i<=n; i+=i&-i)
		++ft[i];
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ifstream cin("sort.in");
	ofstream cout("sort.out");
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0];
		a[i][1]=i;
	}
	memcpy(b, a, sizeof(a[0])*n);
	sort(b, b+n);
	for(int i=n-1, j=n-1; i>=0; --i) {
		upd(b[i][1]);
		while(j>=0&&a[j]>=b[i])
			--j;
		ans+=max(qry(max(b[i][1], j+1)), 1);
	}
	cout << (n>1?ans:0);
}
