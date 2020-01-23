#include <bits/stdc++.h>
using namespace std;

const int mxN=2e6;
int n, c[256], cl[mxN], p[mxN], nl[mxN], lmx[mxN], lmn[mxN], nr[mxN], rmx[mxN], rmn[mxN];
string s;

struct sufar {
	int a[3*mxN+999], b[mxN], c[mxN+2], sa[mxN+1];
	void rd(int *a, int n, int *x, int *y, int m) {
		memset(c, 0, 4*n+4);
		for(int i=0; i<m; ++i)
			++c[a[x[i]]];
		for(int i=0; i<n; ++i)
			c[i+1]+=c[i];
		for(int i=m-1; ~i; --i)
			y[--c[a[x[i]]]]=x[i];
	}
	void ac(int *a, int n) {
		if(n<2)
			return;
		bool z=n%3==1;
		if(z)
			++n;
		int m=0;
		for(int i=1; i<n; i+=3)
			a[n+2+m++]=i;
		for(int i=2; i<n; i+=3)
			a[n+2+m++]=i;
		rd(a+2, n, a+n+2, b, m);
		rd(a+1, n, b, a+n+2, m);
		rd(a, n, a+n+2, b, m);
		for(int i=0, j=0; i<m; ++i) {
			if(!i||a[b[i]]^a[b[i-1]]||a[b[i]+1]^a[b[i-1]+1]||a[b[i]+2]^a[b[i-1]+2])
				++j;
			a[n+2+b[i]/3+(b[i]%3>1?(n+1)/3:0)]=j;
		}
		ac(a+n+2, m);
		for(int i=0, j=0; i<m; ++i) {
			sa[i]=sa[i]<(n+1)/3?1+3*sa[i]:2+3*(sa[i]-(n+1)/3);
			if(sa[i]%3<2)
				a[n+1+j++]=sa[i]-1;
		}
		rd(a, n, a+n+1, b, (n+2)/3);
		for(int i=0; i<m; ++i)
			a[n+1+sa[i]]=i;
		a[n+1+n]=a[n+1+n+1]=-1;
		for(int i=n-1, j1=(n+2)/3-1, j2=m-1; ~j1; --i) {
			if(j2<0) {
				sa[i]=b[j1--];
				continue;
			}
			int k1=b[j1], k2=sa[j2];
			if(a[k1]^a[k2]?a[k1]<a[k2]:(k2%3<2?a[n+1+k1+1]<a[n+1+k2+1]:(a[k1+1]^a[k2+1]?a[k1+1]<a[k2+1]:a[n+1+k1+2]<a[n+1+k2+2]))) {
				sa[i]=k2;
				--j2;
			} else {
				sa[i]=k1;
				--j1;
			}
		}
		if(z)
			for(int i=1; i<n; ++i)
				sa[i-1]=sa[i];
	}
} sa;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s;
	for(int i=0; i<n; ++i)
		++c[s[i]];
	for(int i=0, j=0; i<256; ++i)
		if(c[i])
			c[i]=++j;
	for(int i=0; i<n; ++i)
		sa.a[i]=c[s[i]];
	sa.ac(sa.a, n);
	for(int i=0; i<n; ++i)
		cl[sa.sa[i]]=i+1;
	s+='$';
	for(int i=0, k=0; i<n; ++i, k-=k>0) {
		if(cl[i]>=n)
			continue;
		for(; s[i+k]==s[sa.sa[cl[i]]+k]; ++k);
		p[cl[i]]=k;
	}
	long long ans=0;
	for(int i=1; i<n; ++i) {
		nl[i]=i-1;
		lmx[i]=lmn[i]=sa.sa[i-1];
		while(nl[i]&&p[nl[i]]>=p[i]) {
			lmx[i]=max(lmx[nl[i]], lmx[i]);
			lmn[i]=min(lmn[nl[i]], lmn[i]);
			nl[i]=nl[nl[i]];
		}
	}
	for(int i=n-1; i; --i) {
		nr[i]=i+1;
		rmx[i]=rmn[i]=sa.sa[i];
		while(nr[i]<n&&p[nr[i]]>p[i]) {
			rmx[i]=max(rmx[nr[i]], rmx[i]);
			rmn[i]=min(rmn[nr[i]], rmn[i]);
			nr[i]=nr[nr[i]];
		}
		int b=min(lmn[i], rmn[i]), c=max(lmx[i], rmx[i]), l=min(c-b, p[i]);
		ans=max((long long)l*max(c, n-b-l), ans);
	}
	cout << ans;
}
