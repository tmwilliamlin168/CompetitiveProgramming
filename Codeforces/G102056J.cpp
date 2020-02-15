#include <bits/stdc++.h>
using namespace std;

#define ld long double

const int mxN=2e5;
int t, n, sa[mxN], sa2[mxN], r[2*mxN], r2[mxN], rs, cnt[mxN+2], lcp[mxN], m, c[2*mxN+1][26], e[2*mxN+1][26], d[2*mxN+1], dt;
string s;
bool h[2*mxN+1];
ld dp[2*mxN+1];

void dfs1(int u=1) {
	if(d[u]==n-sa[dt]) {
		++dt;
		h[u]=1;
	}
	while(dt<n) {
		int a=dt?lcp[dt]:0;
		if(d[u]>a)
			break;
		if(d[u]==a) {
			c[u][s[sa[dt]+a]-'a']=m;
			e[u][s[sa[dt]+a]-'a']=sa[dt];
			d[m]=n-sa[dt];
			dfs1(m++);
		} else {
			int &b=c[u][s[sa[dt]+d[u]]-'a'];
			c[m][s[sa[dt-1]+a]-'a']=b;
			e[m][s[sa[dt-1]+a]-'a']=sa[dt-1];
			b=m;
			d[m]=a;
			dfs1(m++);
		}
	}
}

void dfs2(int u=1, int p=0) {
	if(!h[u]) {
		for(int i=0; i<26; ++i) {
			if(c[u][i]) {
				dfs2(c[u][i], u);
				dp[u]+=1/dp[c[u][i]];
			}
		}
		dp[u]=1/dp[u];
	}
	dp[u]+=d[u]-d[p];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	cout << fixed << setprecision(16);
	while(t--) {
		cin >> s;
		n=s.size();
		for(int i=0; i<n; ++i)
			r[i]=s[i]-'a'+1;
		rs=26;
		for(int l=1; l<=n; l*=2) {
			for(int i=0; i<n; ++i)
				++cnt[r[i+l]+1];
			for(int i=0; i<rs; ++i)
				cnt[i+1]+=cnt[i];
			for(int i=0; i<n; ++i)
				sa2[cnt[r[i+l]]++]=i;
			memset(cnt, 0, 4*(rs+2));
			for(int i=0; i<n; ++i)
				++cnt[r[i]+1];
			for(int i=0; i<rs; ++i)
				cnt[i+1]+=cnt[i];
			for(int i=0; i<n; ++i)
				sa[cnt[r[sa2[i]]]++]=sa2[i];
			memset(cnt, 0, 4*(rs+2));
			rs=0;
			for(int i=0; i<n; ++i) {
				if(!i||r[sa[i]]!=r[sa[i-1]]||r[sa[i]+l]!=r[sa[i-1]+l])
					++rs;
				r2[sa[i]]=rs;
			}
			memcpy(r, r2, 4*n);
		}
		s+='$';
		for(int i=0, k=0; i<n; ++i, k-=k>0) {
			if(r[i]>=n)
				continue;
			for(; s[i+k]==s[sa[r[i]]+k]; ++k);
			lcp[r[i]]=k;
		}
		memset(r, 0, 4*2*n);
		m=2;
		dt=0;
		memset(c, 0, sizeof(c[0])*(2*n+1));
		memset(h, 0, 2*n+1);
		dfs1();
		memset(dp, 0, sizeof(ld)*m);
		dfs2();
		cout << dp[1] << "\n";
	}
}
