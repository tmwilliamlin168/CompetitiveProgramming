#include <bits/stdc++.h>
using namespace std;

#define ll long long

template<typename T> struct cp {
	T x, y;
	cp<T> operator+(const cp &o) const {
		return {x+o.x, y+o.y};
	}
	cp<T> operator*(const cp &o) const {
		return {x*o.x-y*o.y, x*o.y+y*o.x};
	}
};

template<typename T> void fft(vector<cp<T>> &a, bool iv) {
	int n=a.size();
	for(int i=0, j=0; i<n; ++i) {
		if(i>j)
			swap(a[i], a[j]);
		for(int k=n/2; (j^=k)<k; k/=2);
	}
	for(int st=1; 2*st<=n; st*=2) {
		T an=acos((T)-1)/st*(iv?-1:1);
		cp<T> wn={cos(an), sin(an)}, wi={1, 0};
		for(int i=0; i<n; i+=2*st) {
			cp<T> wi={1, 0};
			for(int j=i; j<i+st; ++j, wi=wi*wn) {
				cp<T> u=a[j], v=wi*a[j+st];
				a[j]=u+v;
				a[j+st]=u+v*cp<T>{-1, 0};
			}
		}
	}
	if(iv)
		for(int i=0; i<n; ++i)
			a[i].x/=n;
}

const int mxN=2e5;
int n, x, ps[mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x;
	for(int i=0; i<n; ++i) {
		int ai;
		cin >> ai;
		ps[i+1]=ps[i]+(ai<x);
	}
	vector<cp<double>> a(1<<19), b(1<<19);
	for(int i=0; i<=n; ++i) {
		++a[ps[i]].x;
		++b[n-ps[i]].x;
	}
	fft(a, 0);
	fft(b, 0);
	for(int i=0; i<1<<19; ++i)
		a[i]=a[i]*b[i];
	fft(a, 1);
	cout << ((ll)round(a[n].x)-n-1)/2;
	for(int i=n+1; i<=2*n; ++i)
		cout << " " << (ll)round(a[i].x);
}
