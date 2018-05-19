#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6;
int n;
ll a, b, c, xs, qum[mxN+1], qub[mxN+1], qh=0, qt=1, ans;

inline void upd(ll mi, ll bi) {
	while(qt-qh>=2&&(qub[qt-1]-qub[qt-2])*(qum[qt-1]-mi)>=(qum[qt-2]-qum[qt-1])*(bi-qub[qt-1]))
		--qt;
	qum[qt]=mi, qub[qt]=bi, ++qt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> a >> b >> c;
	for(int i=0; i<n; ++i) {
		int xi;
		cin >> xi, xs+=xi;
		ans=(a*xs+b)*xs+c;
		while(qh+1<qt&&qum[qh]*xs+qub[qh]<qum[qh+1]*xs+qub[qh+1])
			++qh;
		ans+=qum[qh]*xs+qub[qh];
		upd(-2*a*xs, (a*xs-b)*xs+ans);
	}
	cout << ans;
}
