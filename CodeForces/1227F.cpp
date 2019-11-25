#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5, M=998244353, G=3;
int n, h[mxN], k, m;
ll ans;

ll pm(ll b, int p) {
	ll r=1;
	for(; p; b=b*b%M, p/=2)
		if(p&1)
			r=r*b%M;
	return r;
}

struct ntt {
	ll rt[1<<19];
	void fi(int n) {
		rt[n/2]=1;
		rt[n/2+1]=pm(G, (M-1)/n);
		for(int i=n/2+2; i<n; ++i)
			rt[i]=rt[i-1]*rt[n/2+1]%M;
		for(int i=n/2; --i; )
			rt[i]=rt[2*i];
	}
	void ac(vector<ll> &a) {
		int n=a.size();
		for(int i=0, j=0; i<n; ++i) {
			if(i>j)
				swap(a[i], a[j]);
			for(int k=n/2; (j^=k)<k; k/=2);
		}
		for(int st=1; 2*st<=n; st*=2) {
			for(int i=0; i<n; i+=2*st) {
				for(int j=i; j<i+st; ++j) {
					ll z=rt[j-i+st]*a[j+st]%M;
					a[j+st]=a[j]-z;
					if(a[j+st]<0)
						a[j+st]+=M;
					a[j]+=z;
					if(a[j]>=M)
						a[j]-=M;
				}
			}
		}
	}
} nt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	nt.fi(1<<19);
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> h[i];
	for(int i=0; i<n; ++i)
		if(h[i]^h[(i+1)%n])
			++m;
	vector<ll> b{1, k-2, 1};
	b.resize(1<<19);
	nt.ac(b);
	for(int i=0; i<1<<19; ++i)
		b[i]=pm(b[i], m)*pm(1<<19, M-2)%M;
	for(int i=1, j=(1<<19)-1; i<j; ++i, --j)
		swap(b[i], b[j]);
	nt.ac(b);
	for(int i=m+1; i<=2*m; ++i)
		ans=(ans+b[i])%M;
	for(int i=0; i<n; ++i)
		if(h[i]==h[(i+1)%n])
			ans=ans*k%M;
	cout << ans%M;
}
