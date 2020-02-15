#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, bs=400, mxBC=(mxN-1)/bs+1, M=998244353;
int n, k, dp[mxN+1], lst[mxN+1], nxt[mxN], b[mxN], c[mxBC][2*mxN+1], d[mxBC];

void am(int &a, int b) {
	a+=b;
	if(a>=M)
		a-=M;
}

void upd(int l1, int r1, int x) {
	for(int bi=l1/bs; bi<=r1/bs; ++bi) {
		int l2=bi*bs, r2=min((bi+1)*bs, n)-1;
		if(l1<=l2&&r2<=r1) {
			d[bi]+=x;
			continue;
		}
		l2=max(l1, l2);
		r2=min(r1, r2);
		for(; l2<=r2; ++l2) {
			if(x==1)
				am(c[bi][b[l2]+n], M-dp[l2]);
			b[l2]+=x;
			if(x==-1)
				am(c[bi][b[l2]+n], dp[l2]);
		}
	}
}

int qry(int l1, int r1) {
	int e=0;
	for(int bi=l1/bs; bi<=r1/bs; ++bi) {
		int l2=bi*bs, r2=min((bi+1)*bs, n)-1;
		if(l1<=l2&&r2<=r1) {
			am(e, c[bi][k+n-d[bi]]);
			continue;
		}
		l2=max(l1, l2);
		r2=min(r1, r2);
		for(; l2<=r2; ++l2)
			if(b[l2]+d[bi]<=k)
				am(e, dp[l2]);
	}
	return e;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	dp[0]=1;
	memset(lst, -1, sizeof(lst));
	for(int i=0, ai; i<n; ++i) {
		cin >> ai;
		nxt[i]=lst[ai];
		lst[ai]=i;
		if(i%bs==bs-1||i==n-1) {
			memset(c[i/bs], 0, sizeof(c[0]));
			for(int l=i/bs*bs; l<=i; ++l)
				am(c[i/bs][b[l]+n], dp[l]);
			for(int j=1; j<=2*n; ++j)
				am(c[i/bs][j], c[i/bs][j-1]);
		}
		upd(nxt[i]+1, i, 1);
		if(nxt[i]!=-1)
			upd(nxt[nxt[i]]+1, nxt[i], -1);
		dp[i+1]=qry(0, i);
	}
	cout << dp[n];
}
