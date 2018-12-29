#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int M=998244353, G=3;

ll pm(ll b, int p) {
	ll r=1;
	while(p) {
		if(p&1)
			r=r*b%M;
		b=b*b%M;
		p/=2;
	}
	return r;
}

void ntt(vector<ll> &a, bool iv) {
	int n=a.size();
	for(int i=0, j=0; i<n; ++i) {
		if(i>j)
			swap(a[i], a[j]);
		for(int k=n/2; (j^=k)<k; k/=2);
	}
	for(int st=1, id=1; 2*st<=n; st*=2, ++id) {
		ll wn=pm(G, iv?(M-1-(M-1>>id)):(M-1>>id));
		for(int i=0; i<n; i+=2*st) {
			ll wi=1;
			for(int j=i; j<i+st; ++j, wi=wi*wn%M) {
				ll u=a[j], v=wi*a[j+st]%M;
				a[j]=u+v;
				if(a[j]>=M)
					a[j]-=M;
				a[j+st]=u-v;
				if(a[j+st]<0)
					a[j+st]+=M;
			}
		}
	}
	if(iv) {
		ll in=pm(n, M-2);
		for(int i=0; i<n; ++i)
			a[i]=a[i]*in%M;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, k, di;
	cin >> n >> k;
	vector<ll> a(1<<20);
	while(k--)
		cin >> di, a[di]=1;
	ntt(a, 0);
	for(int i=0; i<1<<20; ++i)
		a[i]=pm(a[i], n/2);
	ntt(a, 1);
	ll ans=0;
	for(int i=0; i<1<<20; ++i)
		ans+=a[i]*a[i]%M;
	cout << ans%M;
}
