#include <bits/stdc++.h>
using namespace std;

#define ll long long

class CollectingCoins {
public:
	vector<int> v, d;
	vector<ll> a;
	vector<ll> f(int m, int k) {
		if((m+k)%2==1&&m) {
			vector<ll> b=f(m-1, k);
			b.push_back(0);
			for(int i=1; i<=k; ++i)
				b.back()=max(b[2*k-i]+a[i], b.back());
			return vector<ll>(b.begin()+1, b.end());
		} else if((m+k)%2==0&&m>=k) {
			vector<ll> b=f((m+k)/2-k, k), c(2*k-1);
			for(int i=1; i<k; ++i)
				for(int j=0; j<k; ++j)
					c[i-1]=max(b[k-1-j]+b[i-1+j], c[i-1]);
			for(int i=k; i<2*k; ++i)
				for(int j=1; j<=k; ++j)
					c[i-1]=max(b[2*k-1-j]+b[i-k+j-1], c[i-1]);
			return c;
		} else {
			a=vector<ll>(m+2*k);
			for(int i=1; i<a.size(); ++i) {
				if(i<=k)
					for(int j=0; j<v.size(); ++j)
						a[i]+=(i-1-(i-1)/d[j])*v[j];
			   	for(int j=1; j<min(k+1, i); ++j)
					a[i]=max(a[j]+a[i-j], a[i]);
			}
			return vector<ll>(a.begin()+m+1, a.end());
		}
	}
	ll maxValue(int m, int k, vector<int> v, vector<int> d) {
		this->v=v;
		this->d=d;
		return f(m+1, k)[0];
	}
};
