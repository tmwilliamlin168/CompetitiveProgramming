#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6, M=998244353;
string a, l, r, l2, r2;
long long dp[mxN+2];
int n, z1[2*mxN+1], z2[2*mxN+1];

void cz(string &s, int z[2*mxN+1]) {
	int l=0, r=0;
	for(int i=1; i<s.size(); ++i) {
		if(i>r) {
			l=r=i;
			while(r<s.size()&&s[r-l]==s[r])
				++r;
			z[i]=r-l;
			--r;
		} else {
			int k=i-l;
			if(z[k]>=r-i+1) {
				l=i;
				while(r<s.size()&&s[r-l]==s[r])
					++r;
				z[i]=r-l;
				--r;
			} else
				z[i]=z[k];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> a >> l >> r;
	n=a.size();
	l2=l+'!'+a;
	r2=r+'!'+a;
	cz(l2, z1);
	cz(r2, z2);
	dp[0]=1;
	dp[1]=-1;
	for(int i=0; i<n; ++i) {
		dp[i]=(dp[i]%M+M)%M;
		dp[i+1]+=dp[i];
		if(a[i]=='0') {
			if(l=="0") {
				dp[i+1]+=dp[i];
				dp[i+2]-=dp[i];
			}
			continue;
		}
		int al=l.size()+1, ar=r.size(), zl=z1[l.size()+1+i], zr=z2[r.size()+1+i];
		if(i+l.size()<=n&&(zl>=l.size()||a[i+zl]>l[zl]))
			--al;
		if(i+r.size()<=n&&(zr>=r.size()||a[i+zr]<r[zr]))
			++ar;
		dp[min(i+al, n+1)]+=dp[i];
		dp[min(i+ar, n+1)]-=dp[i];
	}
	cout << (dp[n]%M+M)%M;
}
