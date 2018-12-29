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

unsigned int br(unsigned int a, int l) {
	a=((a&0x55555555U)<<1)|((a&0xAAAAAAAAU)>>1);
	a=((a&0x33333333U)<<2)|((a&0xCCCCCCCCU)>>2);
	a=((a&0x0F0F0F0FU)<<4)|((a&0xF0F0F0F0U)>>4);
	a=((a&0x00FF00FFU)<<8)|((a&0xFF00FF00U)>>8);
	a=((a&0x0000FFFFU)<<16)|((a&0xFFFF0000U)>>16);
	return a>>(32-l);
}

void ntt(vector<ll> &a, vector<ll> &b, bool iv) {
	int n=a.size(), lg=__lg(n);
	for(int i=0; i<n; ++i)
		b[br(i, lg)]=a[i];
	for(int st=1, id=1; 2*st<=n; st*=2, ++id) {
		ll wn=pm(G, iv?(M-1-(M-1>>id)):(M-1>>id)), wi=1;
		for(int i=0; i<st; ++i, wi=wi*wn%M) {
			for(int j=i; j<n; j+=2*st) {
				ll u=b[j], v=wi*b[j+st]%M;
				b[j]=u+v;
				if(b[j]>=M)
					b[j]-=M;
				b[j+st]=u-v;
				if(b[j+st]<0)
					b[j+st]+=M;
			}
		}
	}
	if(iv) {
		ll in=pm(n, M-2);
		for(int i=0; i<n; ++i)
			b[i]=b[i]*in%M;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, k, di;
	cin >> n >> k;
	vector<ll> a(1<<20), b(1<<20);
	while(k--)
		cin >> di, a[di]=1;
	ntt(a, b, 0);
	for(int i=0; i<1<<20; ++i)
		b[i]=pm(b[i], n/2);
	ntt(b, a, 1);
	ll ans=0;
	for(int i=0; i<1<<20; ++i)
		ans+=a[i]*a[i]%M;
	cout << ans%M;
}
