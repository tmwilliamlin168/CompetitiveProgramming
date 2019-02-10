#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, k, t1, t2, ans, d[mxN-1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> t2;
		if(i)
			d[i-1]=t2-t1-1;
		t1=t2;
	}
	ans=n;
	sort(d, d+n-1);
	for(int i=0; i<n-k; ++i)
		ans+=d[i];
	cout << ans;
}
