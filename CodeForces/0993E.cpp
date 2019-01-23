#include <bits/stdc++.h>
using namespace std;

template<typename T> struct cp {
	T x, y;
	cp<T> operator+(const cp &o) const {
		return {x+o.x, y+o.y};
	}
	cp<T> operator*(const cp &o) const {
		return {x*o.x-y*o.y, x*o.y+y*o.x};
	}
};
template<typename T> struct fft {
	static const int mxN=1<<19;
	cp<T> rt[mxN];
	void fi(int n) {
		T PI=acos((T)-1);
		for(int i=0; i<n/2; ++i) {
			T an=2*PI*i/n;
			rt[i+n/2]={cos(an), sin(an)};
		}
		for(int i=n/2; --i; )
			rt[i]=rt[2*i];
	}
	void ac(vector<cp<T>> &a) {
		int n=a.size();
		for(int i=0, j=0; i<n; ++i) {
			if(i>j)
				swap(a[i], a[j]);
			for(int k=n/2; (j^=k)<k; k/=2);
		}
		for(int st=1; 2*st<=n; st*=2) {
			for(int i=0; i<n; i+=2*st) {
				for(int j=i; j<i+st; ++j) {
					cp<T> z=rt[j-i+st]*a[j+st];
					a[j+st]=a[j]+cp<T>{-1, 0}*z;
					a[j]=a[j]+z;
				}
			}
		}
	}
	void mul(vector<cp<T>> &g, vector<cp<T>> &h) {
		int n=g.size();
		ac(g);
		for(int i=0; i<n; ++i) {
			int j=(n-i)&(n-1);
			cp<T> g2=g[i]*g[i];
			g2.x=-g2.x;
			h[i]=(g[j]*g[j]+g2)*cp<T>{(T)0, (T)-1/4/n};
		}
		ac(h);
	}
};
fft<double> f;

const int mxN=2e5;
int n, x, ps[mxN+1], ai;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x;
	for(int i=0; i<n; ++i) {
		cin >> ai;
		ps[i+1]=ps[i]+(ai<x);
	}
	vector<cp<double>> a(1<<19), b(1<<19);
	for(int i=0; i<=n; ++i) {
		++a[ps[i]].x;
		++a[n-ps[i]].y;
	}
	f.fi(1<<19);
	f.mul(a, b);
	cout << ((long long)round(b[n].x)-n-1)/2;
	for(int i=n+1; i<=2*n; ++i)
		cout << " " << (long long)round(b[i].x);
}
