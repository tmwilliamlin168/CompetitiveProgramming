/*
	- Any two functions only intersect once, so we can use CHT
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, h[mxN], a1[mxN], a2[mxN], sr[1000001], qu[mxN];

double ix(int i, int j) {
	double a=(j-i)/2.0/(h[j]-h[i])-(h[j]-h[i])/2.0;
	return a*a+j;
}

void solve(int a[mxN]) {
	for(int i=0, qh=0, qt=0; i<n; ++i) {
		if(!i||h[qu[qt-1]]<h[i]) {
			while(qt>qh&&h[i]>=h[qu[qt-1]]+sr[i-qu[qt-1]]||qt-qh>1&&ix(qu[qt-2], qu[qt-1])>ix(qu[qt-1], i))
				--qt;
			qu[qt++]=i;
		}
		while(qt-qh>1&&i>ix(qu[qh], qu[qh+1]))
			++qh;
		a[i]=h[qu[qh]]+sr[i-qu[qh]];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=1; i<=1000; ++i)
		for(int j=(i-1)*(i-1)+1; j<=i*i; ++j)
			sr[j]=i;
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> h[i];
	solve(a1);
	for(int i=0; i<n-1-i; ++i)
		swap(h[i], h[n-1-i]);
	solve(a2);
	for(int i=0; i<n; ++i)
		cout << max(a1[i], a2[n-1-i])-h[n-1-i] << "\n";
}
