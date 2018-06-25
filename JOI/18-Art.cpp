#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second

const int mxN=5e5;
int n;
ll mx, ans;
pll ps[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> ps[i].fi >> ps[i].se;
	sort(ps, ps+n+1);
	for(int i=1; i<=n; ++i) {
		ps[i].se+=ps[i-1].se;
		mx=max(ps[i].fi-ps[i-1].se, mx);
		ans=max(ps[i].se-ps[i].fi+mx, ans);
	}
	cout << ans;
}
