/*
	- Given an element, we can also find the previous element
	- Divide and conquer on the array
		- Use 2 pointers starting from the middle to count the answer
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int M=1e9+7;
int n;
ll s, a, b, c, ia, ans;

ll iv(ll a, ll m) {
	return a<=1?a:(1-iv(m%a, a)*m)/a+m;
}

void dc(int l=0, int r=n-1, ll t=s) {
	if(l>r)
		return;
	int m=(l+r)/2;
	ll vl=t;
	for(int i=l; i<m; ++i)
		vl=(vl*a+b)%c;
	if(l==r) {
		ans+=vl;
		return;
	}
	ll vr=(vl*a+b)%c, ml=-1, mr=-1;
	dc(l, m, t);
	dc(m+1, r, vr);
	for(int il=m+1, ir=m; il>l||ir<r; ) {
		if(vl<vr) {
			ml=max(vl, ml);
			vl=--il>l?(vl-b+c)*ia%c:2e9;
			ans+=ml*(ir-m)%M;
		} else {
			mr=max(vr, mr);
			vr=++ir<r?(vr*a+b)%c:2e9;
			ans+=mr*(m+1-il)%M;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s >> a >> b >> c;
	ia=iv(a, c);
	dc();
	cout << ans%M;
}
