#include <bits/stdc++.h>
using namespace std;

#define ar array
#define ld long double

const int mxN=1e5;
const ld PI=acos(-1);
int n, m, st[mxN][17];
ar<int, 2> a[mxN];
ar<ld, 2> b[mxN], c[2*mxN];
ld lb, rb=1e6, d[mxN], th[mxN];

bool chk(ld r) {
	for(int i=0; i<n; ++i) {
		ld ac=acos(r/d[i]);
		b[i]={th[i]-ac, th[i]+ac};
		if(b[i][0]<0) {
			b[i][0]+=2*PI;
			b[i][1]+=2*PI;
		}
	}
	sort(b, b+n);
	int cs=0;
	for(int i=0; i<n; ++i) {
		while(cs&&c[cs-1][1]>=b[i][1])
			--cs;
		if(!cs||c[0][1]>b[i][1]-2*PI)
			c[cs++]=b[i];
	}
	for(int i=0; i<cs; ++i) {
		c[cs+i]=c[i];
		c[cs+i][0]+=2*PI;
		c[cs+i][1]+=2*PI;
	}
	for(int i=0, j=0; i<cs; ++i) {
		while(j<i+cs&&c[j][0]<=c[i][1])
			++j;
		st[i][0]=j-i;
	}
	for(int k=1; k<17; ++k)
		for(int i=0; i<cs; ++i)
			st[i][k]=st[i][k-1]+st[(i+st[i][k-1])%cs][k-1];
	for(int s=0; s<cs; ++s) {
		int co=0;
		for(int k=16, u=0, i=s; ~k; --k) {
			if(u+(1<<k)<=m) {
				co+=st[i][k];
				i=(i+st[i][k])%cs;
				u+=1<<k;
			}
		}
		if(co>=cs)
			return 1;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i][0] >> a[i][1];
	for(int i=0; i<n; ++i) {
		d[i]=hypot(a[i][0], a[i][1]);
		rb=min(d[i], rb);
		th[i]=atan2(a[i][1], a[i][0]);
	}
	while(rb-lb>1e-7) {
		ld mb=(lb+rb)/2;
		if(chk(mb))
			lb=mb;
		else
			rb=mb;
	}
	cout << fixed << setprecision(9) << lb;
}
