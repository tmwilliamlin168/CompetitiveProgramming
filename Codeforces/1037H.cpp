#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxQ=2e5;
string s, x[mxQ];
int n, q, sa[mxN], sa2[mxN], r[2*mxN-1], r2[mxN], rs=26, cnt[mxN+2], lcp[mxN], m=2, c[2*mxN+1][26], e[2*mxN+1][26], d[2*mxN+1], ds[2*mxN+1], dt=0, ans[mxQ];
vector<array<int, 3>> tp[mxN];

struct segtree {
	int a[1<<18];
	void upd(int i, int x) {
		for(i+=n; i; i/=2)
			a[i]=min(x, a[i]);
	}
	int qry(int l, int r) {
		int b=INT_MAX;
		for(l+=n, r+=n+1; l<r; ++l/=2, r/=2) {
			if(l&1)
				b=min(a[l], b);
			if(r&1)
				b=min(a[r-1], b);
		}
		return b;
	}
} st;

void dfs(int u) {
	ds[u]+=dt;
	if(d[u]==n-sa[dt])
		++dt;
	while(dt<n) {
		int a=dt?lcp[dt]:0;
		if(d[u]>a)
			break;
		if(d[u]==a) {
			c[u][s[sa[dt]+a]-'a']=m;
			e[u][s[sa[dt]+a]-'a']=sa[dt];
			d[m]=n-sa[dt];
			dfs(m++);
		} else {
			int &b=c[u][s[sa[dt]+d[u]]-'a'];
			c[m][s[sa[dt-1]+a]-'a']=b;
			e[m][s[sa[dt-1]+a]-'a']=sa[dt-1];
			ds[m]=ds[b]-dt;
			b=m;
			d[m]=a;
			dfs(m++);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s >> q;
	n=s.size();
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
		lcp[r[i]]=k;
	}
	dfs(1);
	for(int i=0; i<q; ++i) {
		int l, r;
		cin >> l >> r >> x[i], --l, --r;
		for(int j=1; j; ) {
			if(d[j]>=x[i].size()) {
				tp[ds[j]].push_back({l, r-x[i].size(), i});
				break;
			}
			for(int k=x[i][d[j]]-'a'+1; k<26; ++k) {
				if(c[j][k]) {
					tp[ds[c[j][k]]].push_back({l, r-d[j], i});
					break;
				}
			}
			int a=c[j][x[i][d[j]]-'a'], b=e[j][x[i][d[j]]-'a'];
			for(int k=d[j]+1; k<d[a]; ++k) {
				if(k>=x[i].size()||s[b+k]!=x[i][k]) {
					if(k>=x[i].size()||s[b+k]>x[i][k])
						tp[ds[a]].push_back({l, r-k, i});
					a=0;
					break;
				}
			}
			j=a;
		}
	}
	memset(st.a, 0x3F, sizeof(st.a));
	memset(ans, 0x3F, 4*q);
	for(int i=n-1; i>=0; --i) {
		st.upd(sa[i], i);
		for(array<int, 3> a : tp[i])
			ans[a[2]]=min(st.qry(a[0], a[1]), ans[a[2]]);
	}
	for(int i=0; i<q; ++i) {
		if(ans[i]>=n)
			cout << "-1";
		else
			for(int j=0; !j||(j<=x[i].size()&&s[sa[ans[i]]+j-1]==x[i][j-1]); ++j)
				cout << s[sa[ans[i]]+j];
		cout << "\n";
	}
}
