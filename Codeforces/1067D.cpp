#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxlgT=33;
int n, a[mxN], b[mxN], c[mxN], m, d[mxN];
ll t, ct;
double p[mxN], bp, e[mxN-1], f[mxlgT+1][3][3], dp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> t;
	for(int i=0; i<n; ++i) {
		cin >> a[i] >> b[i] >> p[i];
		bp=max(b[i]*p[i], bp);
		c[i]=i;
	}
	sort(c, c+n, [&](const int &i, const int &j) {
		return p[i]!=p[j]?p[i]<p[j]:a[i]>a[j];
	});
	d[m++]=c[0];
	for(int i=1; i<n; ++i) {
		if(p[c[i]]==p[c[i-1]])
			continue;
		while(m>=2&&(p[c[i]]*a[c[i]]-p[d[m-2]]*a[d[m-2]])/(p[d[m-2]]-p[c[i]])<=(p[d[m-1]]*a[d[m-1]]-p[d[m-2]]*a[d[m-2]])/(p[d[m-2]]-p[d[m-1]]))
			--m;
		e[m-1]=(p[c[i]]*a[c[i]]-p[d[m-1]]*a[d[m-1]])/(p[d[m-1]]-p[c[i]]);
		d[m++]=c[i];
	}
	e[m-1]=bp*t;
	for(int i=0; i<=mxlgT; ++i) {
		f[i][1][1]=f[i][2][2]=1;
		f[i][1][2]=1ll<<i;
	}
	for(int i=0; i<m&&ct<t; ++i) {
		if(e[i]<bp*ct-dp)
			continue;
		f[0][0][0]=1-p[d[i]];
		f[0][0][1]=p[d[i]]*bp;
		f[0][0][2]=p[d[i]]*a[d[i]];
		for(int j=0; j<mxlgT; ++j) {
			for(int k=0; k<3; ++k) {
				f[j+1][0][k]=0;
				for(int l=0; l<3; ++l)
					f[j+1][0][k]+=f[j][0][l]*f[j][l][k];
			}
		}
		for(ll j=mxlgT; j>=0; --j) {
			if(ct+(1ll<<j)<t&&bp*(ct+(1ll<<j))-(f[j][0][0]*dp+f[j][0][1]*ct+f[j][0][2])<e[i]) {
				dp=f[j][0][0]*dp+f[j][0][1]*ct+f[j][0][2];
				ct+=1ll<<j;
			}
		}
		dp=f[0][0][0]*dp+f[0][0][1]*ct+f[0][0][2];
		++ct;
	}
	cout << fixed << setprecision(9) << dp;
}
