#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, c[mxN+1];
ll lb, rb, k, a1, a2=1;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	rb=(ll)n*n;
	while(lb<rb) {
		ll mb=(lb+rb)/2, x=0;
		memset(c+1, 0, 4*n);
		for(int i=2; i<=n; ++i) {
			c[i]+=i*mb/((ll)n*n);
			for(int j=i; (j+=i)<=n; )
				c[j]-=c[i];
			x+=c[i];
		}
		if(x<k)
			lb=mb+1;
		else
			rb=mb;
	}
	for(int i=2; i<=n; ++i) {
		ll c=i*lb/((ll)n*n);
		if(c*a2>a1*i) {
			a1=c;
			a2=i;
		}
	}
	cout << a1 << " " << a2 << endl;
}
