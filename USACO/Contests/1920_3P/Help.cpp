#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e5, mxK=10, M=1e9+7;
int n, k, l[mxN], r[mxN], ir[2*mxN+1], dp[mxK+2][2*mxN+1];
ll f1[mxK+1], dp2[mxK+1][mxK+1], ans;

ll st[1<<19], lz[1<<19];

void app(int i, ll x) {
	st[i]=st[i]*x%M;
	lz[i]=lz[i]*x%M;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=1;
}

ll qry(int l1, int r1, int i=1, int l2=0, int r2=2*n) {
	if(l1<=l2&&r2<=r1) {
		ll x=st[i];
		app(i, 2);
		return x;
	}
	int m2=(l2+r2)/2;
	psh(i);
	int s=(l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
	if(s>=M)
		s-=M;
	st[i]=st[2*i]+st[2*i+1];
	if(st[i]>=M)
		st[i]-=M;
	return s;
}

void bld(int j, int i=1, int l2=0, int r2=2*n) {
	lz[i]=1;
	if(l2==r2) {
		st[i]=dp[j][l2];
		return;
	}
	int m2=(l2+r2)/2;
	bld(j, 2*i, l2, m2);
	bld(j, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
	if(st[i]>=M)
		st[i]-=M;
}

int main() {
	ifstream cin("help.in");
	ofstream cout("help.out");
	
	cin >> n >> k;
	memset(ir, -1, sizeof(ir));
	for(int i=0; i<n; ++i) {
		cin >> l[i] >> r[i];
		ir[r[i]]=i;
	}

	f1[0]=1;
	for(int i=1; i<=k; ++i)
		f1[i]=f1[i-1]*i%M;
	dp2[0][0]=1;
	for(int i=1; i<=k; ++i) {
		for(int j=1; j<=k; ++j) {
			dp2[i][j]=(dp2[i-1][j]*j+dp2[i-1][j-1])%M;
		}
	}

	dp[0][0]=1;
	for(int j=1; j<=k+1; ++j) {
		bld(j-1);
		for(int i=1; i<=2*n; ++i) {
			if(~ir[i])
				dp[j][i]=qry(0, l[ir[i]]-1);
		}
		ans+=qry(0, 2*n)*f1[j-1]%M*dp2[k][j-1]%M;
	}
	cout << ans%M;
}
