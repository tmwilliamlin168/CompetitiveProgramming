/*
	- Optimal solution looks like A -> ancestor of A -> ancestor of B on the same level -> B
		- Just iterate through each level
	- Processing the steps given in the input can be done efficiently by taking advantage of bitwise operations
*/

#include <bits/stdc++.h>
using namespace std;

const int mxD=1e5, bs=62, mxBC=mxD/bs+1;
int sa, sb, ans=2*mxD, a1=0;
long long bva[mxBC], bvb[mxBC];

inline void rd(ll *bv, int &s) {
	bv[0]=1LL<<(bs-1);
	s=1;
	string ms;
	cin >> ms;
	for(char c : ms) {
		if(c=='1') {
			bv[s/bs]&=~(1LL<<(bs-1-s%bs));
			++s;
		} else if(c=='2') {
			bv[s/bs]|=1LL<<(bs-1-s%bs);
			++s;
		} else if(c=='L') {
			bv[(s-1)/bs]-=1LL<<(bs-1-(s-1)%bs);
			for(int i=(s-1)/bs; bv[i]<0; --i) {
				bv[i]+=1LL<<bs;
				--bv[i-1];
			}
		} else if(c=='R') {
			bv[(s-1)/bs]+=1LL<<(bs-1-(s-1)%bs);
			for(int i=(s-1)/bs; bv[i]>=1LL<<bs; --i) {
				bv[i]-=1LL<<bs;
				++bv[i-1];
			}
		} else
			--s;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	rd(bva, sa);
	rd(bvb, sb);
	for(int i=0; i<min(sa, sb)&&abs(a1)<=ans; ++i) {
		a1=2*a1+(bva[i/bs]>>(bs-1-i%bs)&1)-(bvb[i/bs]>>(bs-1-i%bs)&1);
		ans=min(abs(a1)+sa-i+sb-i-2, ans);
	}
	cout << ans;
}
