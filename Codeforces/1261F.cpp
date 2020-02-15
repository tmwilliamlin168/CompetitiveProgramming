#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=100, M=998244353;
const ll P=1ll<<60;
int n1, n2;
ll l1[mxN], r1[mxN], l2[mxN], r2[mxN], ans;
vector<array<ll, 2>> v;

void ins(ll l, ll a, bool b) {
	if(b) {
		v.push_back({l, 1});
		v.push_back({l+a,  -1});
	} else {
		v.push_back({P-l-a, 1});
		v.push_back({P-l, -1});
	}
}

void pr(ll l1, ll a1, ll l2, ll a2, bool b) {
	if(a1<0||a2<0)
		return;
	for(int i=59; ~i; --i) {
		if(a1<1ll<<i&&a2<1ll<<i)
			continue;
		if(a1>=1ll<<i&&a2>=1ll<<i) {
			ins((l1^l2)&~((1ll<<i+1)-1), 1ll<<i+1, b);
			return;
		}
		ins((l1^l2)&~((1ll<<i)-1), 1ll<<i, b);
		if(a1>=1ll<<i) {
			l1^=1ll<<i;
			a1^=1ll<<i;
		}
		if(a2>=1ll<<i) {
			l2^=1ll<<i;
			a2^=1ll<<i;
		}
	}
	ins(l1^l2, 1, b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n1;
	for(int i=0; i<n1; ++i)
		cin >> l1[i] >> r1[i];
	cin >> n2;
	for(int i=0; i<n2; ++i)
		cin >> l2[i] >> r2[i];
	for(int i=0; i<n1; ++i) {
		for(int j=0; j<n2; ++j) {
			ll m1=r1[i]&~(l1[i]<r1[i]?((1ll<<63-__builtin_clzll(l1[i]^r1[i]))-1):0), m2=r2[j]&~(l2[j]<r2[j]?((1ll<<63-__builtin_clzll(l2[j]^r2[j]))-1):0);
			pr(m1, r1[i]-m1, m2, r2[j]-m2, 1);
			pr(m1, r1[i]-m1, P-m2, m2-l2[j]-1, 0);
			pr(P-m1, m1-l1[i]-1, m2, r2[j]-m2, 0);
			pr(P-m1, m1-l1[i]-1, P-m2, m2-l2[j]-1, 1);
		}
	}
	sort(v.begin(), v.end());
	for(int i=0, c=0; i<v.size(); ++i) {
		if(!c)
			ans+=M-(v[i][0]%M)*((v[i][0]-1)%M)%M;
		c+=v[i][1];
		if(!c)
			ans+=(v[i][0]%M)*((v[i][0]-1)%M)%M;
	}
	cout << ans%M*499122177%M;
}
