#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, k, q, l1, l2, c1, c2;
ll iv[mxN+1], pi[mxN+1], ans;

void ms(int l=0, int r=n-1, int h=k) {
	if(h<2||l==r) {
		if(!l1||r-l+1==l1) {
			l1=r-l+1;
			++c1;
		} else {
			l2=r-l+1;
			++c2;
		}
		return;
	}
	int m=(l+r)/2;
	ms(l, m, h-1);
	ms(m+1, r, h-1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k >> q;
	iv[1]=1;
	for(int i=2; i<=n; ++i)
		iv[i]=(q-q/i)*iv[q%i]%q;
	for(int i=1; i<=n; ++i)
		pi[i]=(pi[i-1]+iv[i])%q;
	ms();
	if(c1>1)
		for(int i=1; i<=l1; ++i)
			ans+=(pi[l1+i]-pi[i]+q)*c1%q*(c1-1)%q;
	if(c2>1)
		for(int i=1; i<=l2; ++i)
			ans+=(pi[l2+i]-pi[i]+q)*c2%q*(c2-1)%q;
	for(int i=1; i<=l1; ++i)
		ans+=(pi[l2+i]-pi[i]+q)*c1%q*c2%q*2;
	cout << (iv[2]*n%q*(n-1)%q-ans%q+q)*iv[2]%q;
}
