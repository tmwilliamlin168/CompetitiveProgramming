#include <bits/stdc++.h>
using namespace std;

const int B=3e4;
int t, a, b, p, q;
array<int, 2> c[B];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> a >> b >> p >> q;
		for(int i=0; i<B; ++i)
			c[i]={(int)(2ll*p*i%(2*q)), i};
		sort(c, c+B);
		for(int i=1; i<B; ++i)
			if(c[i][0]==c[i-1][0])
				c[i][1]=c[i-1][1];
		array<int, 2> ans{q, b};
		for(; a+B<=b; a+=B) {
			int x=(3ll*q-2ll*p*a%(2*q))%(2*q), p1=(lower_bound(c, c+B, array<int, 2>{x})-c)%B, p2=(upper_bound(c, c+B, array<int, 2>{x})-c+B-1)%B;
			ans=min({array<int, 2>{(int)abs(q-(c[p1][0]+2ll*p*a)%(2*q)), c[p1][1]+a}, array<int, 2>{(int)abs(q-(c[p2][0]+2ll*p*a)%(2*q)), c[p2][1]+a}, ans});
		}
		for(; a<=b; ++a)
			ans=min(array<int, 2>{(int)abs(q-2ll*p*a%(2*q)), a}, ans);
		cout << ans[1] << "\n";
	}
}
