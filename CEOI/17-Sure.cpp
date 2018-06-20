/*
	- If you know which type of outcome you want to bet for, choose the highest price for that outcome
	- If the profit for one of the outcomes is lower, the minimum profit will only increase if more bets for that outcome are bought
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n;
double a[mxN+1], b[mxN+1], ans, sa, sb;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i] >> b[i];
	sort(a, a+n+1);
	sort(b, b+n+1);
	for(int i1=n, i2=n; i1>=0&&i2>=0; ) {
		if(sa<sb)
			sa+=a[i1--];
		else
			sb+=b[i2--];
		ans=max(min(sa, sb)-(n-i1)-(n-i2), ans);
	}
	cout << fixed << setprecision(4) << ans;
}
