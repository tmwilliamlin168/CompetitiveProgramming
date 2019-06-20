#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, c[mxN][2];
ll a1;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0, x, y; i<2*n; ++i) {
		cin >> x >> y;
		if(x<1) {
			a1+=1-x;
			x=1;
		}
		if(x>n) {
			a1+=x-n;
			x=n;
		}
		if(y<1) {
			a1+=1-y;
			y=1;
		}
		if(y>2) {
			a1+=y-2;
			y=2;
		}
		++c[x-1][y-1];
	}
	for(int i1=0, i2=0, j=0; i1<n||i2<n; ) {
		while(!c[j][0]&&!c[j][1])
			++j;
		if(c[j][0]&&i1<=j) {
			--c[j][0];
			a1+=j-i1++;
		} else if(c[j][1]&&i2<=j) {
			--c[j][1];
			a1+=j-i2++;
		} else if(c[j][0]&&i2<=j) {
			--c[j][0];
			a1+=j-i2+++1;
		} else if(c[j][1]&&i1<=j) {
			--c[j][1];
			a1+=j-i1+++1;
		} else {
			c[j+1][0]+=c[j][0];
			c[j+1][1]+=c[j][1];
			a1+=c[j][0]+c[j][1];
			++j;
		}
	}
	cout << a1;
}
