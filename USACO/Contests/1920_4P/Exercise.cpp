#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=7.5e3;
int n, M, M2, pf[9], pfs;
ll ans=1, dp0[mxN+1], dp1[mxN+1], pd[mxN+1], fr[mxN+1][mxN+1];
bool c[mxN+1];

ll pM(ll b, int p) {
	ll r=1;
	for(; p; p/=2, b=b*b%M)
		if(p&1)
			r=r*b%M;
	return r;
}

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};

int main() {
	ifstream cin("exercise.in");
	ofstream cout("exercise.out");
	
	cin >> n >> M;
	M2=M-1;
	FastMod F(M2);
	for(int l=1; l<=n; ++l) {
		fr[l][l-1]=1;
		for(int r=l; r<=n; ++r)
			fr[l][r]=F.reduce(fr[l][r-1]*r);
	}
	for(int p=2; p<=n; ++p) {
		if(c[p])
			continue;
		for(int i=p*p; i<=n; i+=p)
			c[i]=1;
		int p2=p, tp=0;
		while(p2<=n) {
			memset(dp0, 0, 8*n+8);
			memset(dp1, 0, 8*n+8);
			memset(pd, 0, 8*n+8);
			dp0[0]=pd[0]=1;
			for(int i=1; i<=n; ++i) {
				dp0[i]=dp0[i-1];
				dp1[i]=dp1[i-1];
				if(i>=p2) {
					pd[i-p2]=F.reduce(pd[i-p2]*fr[i-p2+1][i-1]);
					dp0[i]-=pd[i-p2];
					if(dp0[i]<0)
						dp0[i]+=M2;
					dp1[i]+=pd[i-p2];
					if(dp1[i]>=M2)
						dp1[i]-=M2;
				}
				pd[i]=dp0[i];
				if(i>=p2)
					pd[i]=F.reduce(pd[i]+pd[i-p2]*i);
				dp0[i]=F.reduce(dp0[i]+dp0[i-1]*i);
				if(i==n) {
					tp+=dp1[n];
					if(tp>=M2)
						tp-=M2;
				}
				dp1[i]=F.reduce(dp1[i]+dp1[i-1]*i);
			}
			p2*=p;
		}
		ans=ans*pM(p, tp)%M;
	}
	cout << ans;
}
