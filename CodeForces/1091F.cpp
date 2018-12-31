#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n;
ll l[mxN], ans, ps[mxN+1], ts;
string s;
bool pw[mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> l[i];
		ans+=l[i];
	}
	cin >> s;
	for(int i=0; i<n; ++i) {
		ps[i+1]=ps[i];
		pw[i+1]=pw[i];
		if(s[i]=='G') {
			ans+=l[i]*4;
			ps[i+1]+=l[i];
		} else if(s[i]=='W') {
			ans+=l[i]*2;
			ps[i+1]+=l[i];
			pw[i+1]=1;
		} else {
			if(l[i]>ps[i])
				ans+=pw[i]?3*(l[i]-ps[i]):5*(l[i]-ps[i]);
			ps[i+1]-=min(l[i], ps[i]);
		}
	}
	for(int i=n-1; i; --i)
		ps[i]=min(ps[i+1], ps[i]);
	for(int i=0; i<n; ++i) {
		ps[i+1]-=ts;
		if(s[i]=='G') {
			ll a=min(ps[i+1], 2*l[i]);
			ans-=2*a;
			ts+=a;
			ps[i+1]-=a;
		}
	}
	for(int i=n-1; i; --i)
		ps[i]=min(ps[i+1], ps[i]);
	ts=0;
	for(int i=0; i<n; ++i) {
		ps[i+1]-=ts;
		if(s[i]=='W') {
			ll a=min(ps[i+1], 2*l[i]);
			ans-=a;
			ts+=a;
			ps[i+1]-=a;
		}
	}
	cout << ans;
}
