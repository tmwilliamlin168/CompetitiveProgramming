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

struct ntt {
	ll rt[1<<20];
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
};
ntt nt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, k, di;
	cin >> n >> k;
	vector<ll> a(1<<20);
	while(k--)
		cin >> di, a[di]=1;
	nt.fi(1<<20);
	nt.ac(a);
	ll in=pm(1<<20, M-2), ans=0;
	for(int i=0; i<1<<20; ++i)
		a[i]=pm(a[i], n/2)*in%M;
	reverse(a.begin()+1, a.end());
	nt.ac(a);
	for(int i=0; i<1<<20; ++i)
		ans+=a[i]*a[i]%M;
	cout << ans%M;
}
