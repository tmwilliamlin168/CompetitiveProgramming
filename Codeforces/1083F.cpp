#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5, bs=300, mxM=1<<14;
int n, k, q, a[mxN+1], b[mxN+1], c[mxN+1], a2, d[mxN], e[mxN], s, l[mxN], r[mxN], pi, vi, bc[(mxN-1)/bs+1][mxM], lz[(mxN-1)/bs+1];
char qt;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;
	for(int i=1; i<=n; ++i)
		cin >> a[i];
	for(int i=1; i<=n; ++i) {
		cin >> b[i];
		c[i-1]=a[i]^a[i-1]^b[i]^b[i-1];
		if(i>k)
			c[i-1]^=c[i-1-k];
	}
	c[n]=c[n-k]^a[n]^b[n];
	for(int i=0; i<k; ++i) {
		for(int j=i; j<=n-k; j+=k) {
			e[s]=c[j];
			++bc[s/bs][e[s]];
			l[j]=s++;
			r[j]=l[j]+(n-k-j)/k;
		}
	}
	for(int i=n-k+1; i<=n; ++i) {
		a2+=c[i]>0;
		d[i%k]=c[i];
	}
	auto a1=[&]() {
		int r=s;
		for(int i=0; i<=(s-1)/bs; ++i)
			r-=bc[i][lz[i]];
		return r;
	};
	cout << (a2?-1:a1()) << "\n";
	while(q--) {
		cin >> qt >> pi >> vi, --pi;
		if(qt=='a') {
			vi^=a[pi+1];
			a[pi+1]^=vi;
		} else {
			vi^=b[pi+1];
			b[pi+1]^=vi;
		}
		for(int i=pi; i<=pi+1; ++i) {
			if(i<=n-k) {
				int li=l[i];
				auto ue=[&]() {
					--bc[li/bs][e[li]];
					e[li]^=vi;
					++bc[li/bs][e[li]];
				};
				for(; li%bs&&li<=r[i]; ++li)
					ue();
				for(; li+bs<=r[i]; li+=bs)
					lz[li/bs]^=vi;
				for(; li<=r[i]; ++li)
					ue();
			}
			a2+=!d[i%k];
			d[i%k]^=vi;
			a2-=!d[i%k];
		}
		cout << (a2?-1:a1()) << "\n";
	}
}
