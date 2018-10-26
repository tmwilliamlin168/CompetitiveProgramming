#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5, mxlgN=17;
int n, q, sa[mxN], sa2[mxN], r[2*mxN-1], r2[mxN], rs=26, cnt[mxN+2], lcp[mxlgN+1][mxN], a, b, ai, m, d[2*mxN+2], p[2*mxN+2];
ll c[2*mxN+2][2];
string s;
vector<array<int, 2>> v;

int lcpq(int l, int r) {
	int k=31-__builtin_clz(r-l+1);
	return min(lcp[k][l], lcp[k][r-(1<<k)+1]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q >> s;
	for(int i=0; i<n; ++i)
		r[i]=s[i]-'a'+1;
	for(int l=1; l<n; l*=2) {
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
		lcp[0][r[i]]=k;
	}
	for(int k=1; k<=mxlgN; ++k)
		for(int i=0; i<=n-(1<<k); ++i)
			lcp[k][i]=min(lcp[k-1][i], lcp[k-1][i+(1<<(k-1))]);
	while(q--) {
		cin >> a >> b;
		for(int i=0; i<a; ++i)
			cin >> ai, v.push_back({ai-1, 0});
		for(int i=0; i<b; ++i)
			cin >> ai, v.push_back({ai-1, 1});
		sort(v.begin(), v.end(), [&](const array<int, 2> &a, const array<int, 2> &b) {
			return r[a[0]]<r[b[0]];
		});
		m=2;
		ll ans=0;
		int u=1;
		for(int i=0; i<a+b; ++i) {
			int td=i?(v[i-1][0]==v[i][0]?n-v[i][0]:lcpq(r[v[i-1][0]], r[v[i][0]]-1)):n-v[i][0];
			while(u>1&&d[p[u]]>=td) {
				ans+=c[u][0]*c[u][1]*(d[u]-d[p[u]]);
				c[p[u]][0]+=c[u][0];
				c[p[u]][1]+=c[u][1];
				u=p[u];
			}
			if(d[u]>td) {
				ans+=c[u][0]*c[u][1]*(d[u]-td);
				d[u]=td;
			}
			d[m]=n-v[i][0];
			++c[m][v[i][1]];
			p[m]=u;
			u=m++;
		}
		while(u>1) {
			ans+=c[u][0]*c[u][1]*(d[u]-d[p[u]]);
			c[p[u]][0]+=c[u][0];
			c[p[u]][1]+=c[u][1];
			u=p[u];
		}
		v.clear();
		memset(c, 0, sizeof(c[0])*m);
		cout << ans << "\n";
	}
}
