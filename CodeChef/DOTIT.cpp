#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define PI 4*atan(1)
#define base TP2D<double>

const int mxN=1e5, bs=1e3;
int t, n, q, rcx, xi, yi, li;
vector<ll> a, b, tb, c[(mxN-1)/bs+1];

template<typename T> struct TP2D {
	T X, Y;
	TP2D() : X(), Y() {}
	TP2D(const T& x, const T& y) : X(x), Y(y) {}
	__attribute__((always_inline)) TP2D& operator=(const TP2D<T>& p) {
		X=p.X, Y=p.Y;
		return *this;
	}
	__attribute__((always_inline)) TP2D<T> operator*(const TP2D<T>& p) const {
		return TP2D<T>(X*p.X-Y*p.Y, X*p.Y+Y*p.X);
	}
	__attribute__((always_inline)) TP2D<T> operator*(const T& p) const {
		return TP2D<T>(p*X, p*Y);
	}
	__attribute__((always_inline)) TP2D<T> operator-(void) const {
		return TP2D<T>(-X, -Y);
	}
	__attribute__((always_inline)) TP2D<T> operator+(const TP2D<T>& p) const {
		return TP2D<T>(X+p.X, Y+p.Y);
	}
};
vector<base> x(n);
void fft(vector<base> &a, bool inv) {
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
				a[i+j+len/2]=u+-v;
				w=w*wlen;
			}
		}
	}
	if(inv)
		for(int i=0; i<n; ++i)
			a[i]=a[i]*(1.0/n);
}
void mul(vll &a, vll &b, vll &c) {
	int n=1;
	while(n<a.size()+b.size()-1)
		n*=2;
	vector<base> y(n);
	for(int i=0; i<b.size(); ++i)
		y[i]=base(b[i], 0);
	if(rcx) {
		x=vector<base>(n);
		for(int i=0; i<a.size(); ++i)
			x[i]=base(a[i], 0);
		fft(x, 0);
		rcx=0;
	}
	fft(y, 0);
	for(int i=0; i<y.size(); ++i)
		y[i]=x[i]*y[i];
	fft(y, 1);
	c.resize(a.size()+b.size()-1);
	for(int i=0; i<c.size(); ++i)
		c[i]=(ll)round(y[i].X);
}

void solve() {
	cin >> n >> q;
	rcx=1;
	a.resize(n);
	for(int i=0; i<n; ++i)
		cin >> a[i];
	b.resize(n);
	tb=vector<ll>(bs);
	for(int i=0; i<n; ++i) {
		cin >> b[i];
		tb[i%bs]=b[i];
		if(i%bs==bs-1||i==n-1) {
			reverse(tb.begin(), tb.end());
			mul(a, tb, c[i/bs]);
			tb=vector<ll>(bs);
		}
	}
	while(q--) {
		cin >> xi >> yi >> li, --xi, --yi;
		ll ans=0;
		while(yi%bs&&li) {
			ans+=a[xi++]*b[yi++];
			--li;
		}
		while(li>=bs) {
			ans+=c[yi/bs][bs-1+xi];
			xi+=bs;
			yi+=bs;
			li-=bs;
		}
		while(li) {
			ans+=a[xi++]*b[yi++];
			--li;
		}
		cout << ans << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
