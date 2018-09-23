/*
	- http://codeforces.com/blog/entry/60047
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define vll vector<ll>
#define PI 4*atan(1)
#define base TP2D<double>
template<typename T> struct TP2D {
	T X, Y;
	TP2D() : X(), Y() {}
	TP2D(const T& x, const T& y) : X(x), Y(y) {}
	inline TP2D& operator=(const TP2D<T>& p) {
		X=p.X, Y=p.Y;
		return *this;
	}
	inline TP2D<T> operator*(const TP2D<T>& p) const {
		return TP2D<T>(X*p.X-Y*p.Y, X*p.Y+Y*p.X);
	}
	inline TP2D<T> operator*(const T& p) const {
		return TP2D<T>(p*X, p*Y);
	}
	inline TP2D<T> operator-(void) const {
		return TP2D<T>(-X, -Y);
	}
	inline TP2D<T> operator+(const TP2D<T>& p) const {
		return TP2D<T>(X+p.X, Y+p.Y);
	}
	inline TP2D<T> operator-(const TP2D<T>& p) const {
		return *this+(-p);
	}
};
inline void fft(vector<base> &a, bool inv) {
	int n=a.size();
	for(int i=1, j=0; i<n; ++i) {
		int bit=n>>1;
		for(; j>=bit; bit>>=1)
			j-=bit;
		j+=bit;
		if(i<j)
			swap(a[i], a[j]);
	}
	for(int len=2; len<=n; len<<=1) {
		double ang=2*PI/len*(inv?-1:1);
		base wlen(cos(ang), sin(ang));
		for(int i=0; i<n; i+=len) {
			base w(1, 0);
			for(int j=0; j<len/2; ++j) {
				base u=a[i+j], v=a[i+j+len/2]*w;
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w = w*wlen;
			}
		}
	}
	if(inv)
		for(int i=0; i<n; ++i)
			a[i]=a[i]*(1.0/n);
}
inline vll mul(const vll & a, const vll & b) {
	int n=1;
	while (n<a.size()+b.size())
		n*=2;
	vector<base> x(n), y(n);
	for(int i=0; i<a.size(); ++i)
		x[i]=base(a[i], 0);
	for(int i=0; i<b.size(); ++i)
		y[i]=base(b[i], 0);
	fft(x, 0), fft(y, 0);
	for(int i=0; i<x.size(); ++i)
		x[i]=x[i]*y[i];
	fft(x, 1);
	vll res(a.size()+b.size());
	for(int i=0; i<res.size(); ++i)
		res[i]=(ll)round(x[i].X);
	return res;
}

const int mxN=2e5;
int n, x, ps[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x;
	for(int i=0; i<n; ++i) {
		int ai;
		cin >> ai;
		ps[i+1]=ps[i]+(ai<x);
	}
	vll a=vll(n+1), b=vll(n+1);
	for(int i=0; i<=n; ++i) {
		++a[ps[i]];
		++b[n-ps[i]];
	}
	vll c=mul(a, b);
	cout << (c[n]-n-1)/2;
	for(int i=n+1; i<=2*n; ++i)
		cout << " " << (i>=c.size()?0:c[i]);
}
