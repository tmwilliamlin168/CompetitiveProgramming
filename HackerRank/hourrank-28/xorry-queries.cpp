/*
	- Replace a[i] with a[i]^a[i+1]^...^a[i+p-1]
	- Problem becomes range xor updates and range sum queries
	- Consider each of the 17 bits separately (10^5 < 2^17)
	- For the bits that are set, we need to flip 0->1 and 1->0 in a range, so we use 17 segment trees
	- I thought using square root decomposition would be easier to implement than segment tree, but it still wasn't easy
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, sqN=300;
int n, m, p, n2, bs, v[mxN+1], sum[(mxN-1)/sqN+1][17], flp[(mxN-1)/sqN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> p;
	n2=n-p+1, bs=(n2-1)/sqN+1;
	for(int i=0; i<n; ++i)
		cin >> v[i];
	for(int i=n-1; i>=0; --i)
		v[i]^=v[i+1];
	for(int i=0; i<n2; ++i) {
		v[i]^=v[i+p];
		for(int j=0; j<17; ++j)
			sum[i/sqN][j]+=v[i]>>j&1;
	}
	while(m--) {
		int qt, a, b;
		cin >> qt >> a >> b, --a;
		if(qt==1) {
			int s=max(a-p+1, 0);
			a=min(n2-1, a);
			while(s%sqN&&s<=a) {
				for(int j=0; j<17; ++j)
					sum[s/sqN][j]-=v[s]>>j&1;
				v[s]^=b;
				for(int j=0; j<17; ++j)
					sum[s/sqN][j]+=v[s]>>j&1;
				++s;
			}
			while(s<n2&&min(s+sqN, n2)-1<=a) {
				flp[s/sqN]^=b;
				s+=sqN;
			}
			while(s<=a) {
				for(int j=0; j<17; ++j)
					sum[s/sqN][j]-=v[s]>>j&1;
				v[s]^=b;
				for(int j=0; j<17; ++j)
					sum[s/sqN][j]+=v[s]>>j&1;
				++s;
			}
		} else {
			long long ans=0;
			b=min(b, n2)-1;
			while(a%sqN&&a<=b) {
				ans+=v[a]^flp[a/sqN];
				++a;
			}
			while(a<n2&&min(a+sqN, n2)-1<=b) {
				for(int j=0; j<17; ++j) {
					int s=sum[a/sqN][j];
					if(flp[a/sqN]>>j&1)
						s=min(sqN, n2-a)-s;
					ans+=s<<j;
				}
				a+=sqN;
			}
			while(a<=b) {
				ans+=v[a]^flp[a/sqN];
				++a;
			}
			cout << ans << "\n";
		}
	}
}
