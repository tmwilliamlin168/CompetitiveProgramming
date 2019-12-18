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

ll iv[(1<<20)+1];

vector<ll> mult(vector<ll> v, vector<ll> w) {
	int s=v.size()+w.size()-1, t=1;
	while(t<s)
		t*=2;
	v.resize(t);
	w.resize(t);
	nt.ac(v);
	nt.ac(w);
	for(int i=0; i<t; ++i)
		v[i]=v[i]*w[i]%M*iv[t]%M;
	reverse(v.begin()+1, v.end());
	nt.ac(v);
	while(v.back()==0)
		v.pop_back();
	return v;
}

vector<ll> trans(vector<ll> v, ll t) {
	vector<ll> a(v.size()), b(v.size()), r(v.size());
	ll f=1, fi=1, tp=1;
	for(int i=0; i<v.size(); ++i) {
		if(i) {
			f=f*i%M;
			fi=fi*iv[i]%M;
			tp=tp*t%M;
		}
		a[v.size()-1-i]=f*v[i]%M;
		b[i]=tp*fi%M;
	}
	vector<ll> c=mult(a, b);
	fi=1;
	for(int i=0; i<v.size(); ++i) {
		if(i)
			fi=fi*iv[i]%M;
		r[i]=c[v.size()-1-i]*fi%M;
	}
	return r;
}

vector<ll> fp(int r) {
	if(r==0)
		return {1};
	vector<ll> v=fp(r/2), w=trans(v, M-r/2);
	v=mult(v, w);
	if(r&1) {
		v.push_back(0);
		for(int i=v.size()-2; ~i; --i) {
			v[i+1]+=v[i];
			if(v[i+1]>=M)
				v[i+1]-=M;
			v[i]=v[i]*(M-r+1)%M;
		}
	}
	return v;
}

void solve() {
	int n, p, r;
	cin >> n >> p >> r;
	vector<ll> v=fp(r);
	ll nu=pm(p, n+1), ans=0, nup=1, pp=1, inf=1;
	for(int i=0; i<=r; ++i) {
		ll x=pp==1?n+1:(nup-1)*pm(pp-1, M-2)%M;
		ans+=x*v[i]%M;
		nup=nup*nu%M;
		pp=pp*p%M;
		if(i)
			inf=inf*i%M;
	}
	inf=pm(inf, M-2);
	cout << ans%M*inf%M << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	nt.fi(1<<20);
	iv[1]=1;
	for(int i=2; i<=1<<20; ++i)
		iv[i]=M-M/i*iv[M%i]%M;

	int t;
	cin >> t;
	while(t--)
		solve();
}
