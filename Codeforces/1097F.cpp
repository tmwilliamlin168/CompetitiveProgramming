#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxV=7000;
int n, q, qt, xi, yi, zi;
bitset<mxV+1> in[mxV+1], cq[mxV+1], ms[mxN+1], c;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for(int i=1; i<=mxV; ++i) {
		for(int j=0; (j+=i)<=mxV; )
			in[j][i]=1;
		for(int j=i; j<=mxV; ++j) {
			if(j==i?!c[j]:c[j]) {
				for(int k=0; (k+=j)<=mxV; )
					c.flip(k);
				cq[i][j]=1;
			}
		}
		c.reset();
	}
	cin >> n >> q;
	while(q--) {
		cin >> qt;
		if(qt==1) {
			cin >> xi >> yi, --xi;
			ms[xi]=in[yi];
		} else if(qt==2) {
			cin >> xi >> yi >> zi, --xi, --yi, --zi;
			ms[xi]=ms[yi]^ms[zi];
		} else if(qt==3) {
			cin >> xi >> yi >> zi, --xi, --yi, --zi;
			ms[xi]=ms[yi]&ms[zi];
		} else {
			cin >> xi >> yi, --xi;
			cout << ((ms[xi]&cq[yi]).count()&1);
		}
	}
}
