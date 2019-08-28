#include <bits/stdc++.h>
using namespace std;

const int mxN=5e3;
int n, k;
string s;

struct suffixarray {
	static const int mxN=1e4;
	int n, m, sa[mxN], sa2[mxN], cl[2*mxN], cl2[mxN], cnt[mxN+1];
	void ac() {
		for(int l=1; l<n; l*=2) {
			for(int i=0; i<n; ++i)
				++cnt[cl[i+l]];
			for(int i=0; i<m; ++i)
				cnt[i+1]+=cnt[i];
			for(int i=0; i<n; ++i)
				sa2[--cnt[cl[i+l]]]=i;
			memset(cnt, 0, 4*m+4);
			for(int i=0; i<n; ++i)
				++cnt[cl[i]];
			for(int i=0; i<m; ++i)
				cnt[i+1]+=cnt[i];
			for(int i=n-1; ~i; --i)
				sa[--cnt[cl[sa2[i]]]]=sa2[i];
			memset(cnt, 0, 4*m+4);
			m=0;
			for(int i=0; i<n; ++i) {
				if(!i||cl[sa[i-1]]^cl[sa[i]]||cl[sa[i-1]+l]^cl[sa[i]+l])
					++m;
				cl2[sa[i]]=m;
			}
			memcpy(cl, cl2, 4*n);
		}
	}
} sa;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k >> s, --k;
	string s2=s;
	reverse(s2.begin(), s2.end());
	s+=s2;
	sa.n=2*n;
	sa.m=26;
	for(int i=0; i<2*n; ++i)
		sa.cl[i]=s[i]-'a'+1;
	sa.ac();
	int t=-1, l=0, m;
	while(sa.sa[++t]>n);
	t=sa.sa[t];
	while(++l<n&&s[t]==s[t+l]);
	for(m=l; k--&&m<n; m=min(m*2, n));
	for(int i=0; i<m; ++i)
		cout << s[t];
	for(int i=0; i<n-m; ++i)
		cout << s[t+l+i];
}
