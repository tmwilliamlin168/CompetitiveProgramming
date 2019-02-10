/*
	- https://codeforces.com/blog/entry/57637?#comment-413663
*/

#include <bits/stdc++.h>
using namespace std;

inline int in() {
	int result = 0;
	char ch = getchar_unlocked();
	while(true) {
		if(ch >= '0' && ch <= '9')
			break;
		ch = getchar_unlocked();
	}
	result = ch-'0';
	while(true) {
		ch = getchar_unlocked();
		if (ch < '0' || ch > '9')
			break;
		result = result*10 + (ch - '0');
	}
	return result;
}
inline void out(int x) {
	if(!x) {
		putchar_unlocked('0');
		return;
	}
	int rev=x, c=0;
	while(!(rev%10)) {
		++c;
		rev/=10;
	}
	rev=0;
	while(x) {
		rev=rev*10+x%10;
		x/=10;
	}
	while(rev) {
		putchar_unlocked(rev%10+'0');
		rev/=10;
	}
	while(c--)
		putchar_unlocked('0');
}

const int mxL=20, mxQ=1e6;
int l, q, dp[2][1<<mxL];
char s[1<<mxL];

int main() {
	l=in(), q=in();
	for(int i=0; i<1<<l; ++i)
		while(s[i]<'0'||s[i]>'9')
			s[i]=getchar_unlocked();
	for(int j=0; j<2; ++j) {
		for(int i=0; i<1<<l; ++i)
			dp[j][i]=s[i]-'0';
		for(int k=0; k<l; ++k)
			for(int i=0; i<1<<l; ++i)
				if(i>>k&1^j)
					dp[j][i]+=dp[j][i^1<<k];
	}
	while(q--) {
		int na=0, nb=0, nc=0, ma=0, mb=0, mc=0, ans=0;
		for(int i=0; i<l; ++i) {
			char c=getchar_unlocked();
			if(c=='0') {
				++na;
				ma|=1<<(l-1-i);
			} else if(c=='1') {
				++nb;
				mb|=1<<(l-1-i);
			} else if(c=='?') {
				++nc;
				mc|=1<<(l-1-i);
			} else
				--i;
		}
		if(na<nc||nb<nc) {
			bool sw=0;
			if(nb>na) {
				swap(mb, ma);
				sw=1;
			}
			for(int i=mb; ; i=(i-1)&mb) {
				ans+=dp[sw][(sw?(1<<l)-1:0)^i^mb^mc]*(__builtin_popcount(i)&1?-1:1);
				if(!i)
					break;
			}
		} else {
			for(int i=mc; ; i=(i-1)&mc) {
				ans+=s[i|mb]-'0';
				if(!i)
					break;
			}
		}
		out(ans);
		putchar_unlocked('\n');
	}
}
