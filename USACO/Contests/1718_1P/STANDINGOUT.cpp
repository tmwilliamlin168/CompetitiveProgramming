#include <bits/stdc++.h>
using namespace std;

int main() {
	//freopen("standingout.in", "r", stdin);
	//freopen("standingout.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, n2, sumLen=0;
	cin >> n;
	string *s = new string[n];
	for(int i=0; i<n; ++i) {
		cin >> s[i];
		sumLen+=s[i].size();
	}
	n2=sumLen+n;
	int *s2 = new int[n2], *sa = new int[n2], *sa2 = new int[n2], *cl = new int[n2], *cl2 = new int[n2], *cnt = new int[n2], *lcp = new int[n2-1], *pofs = new int[n2];
	for(int i1=0, i2=0; i1<n; ++i1) {
		pofs[i2]=-1;
		s2[i2++]='z'+1+i1;
		for(char c : s[i1]) {
			pofs[i2]=i1;
			s2[i2++]=c;
		}
	}
	for(int i=0; i<n2; ++i) {
		sa[i]=i;
		cl[i]=s2[i];
	}
	sort(sa, sa+n2, [&s2](const int &a, const int &b) {
		return s2[a]==s2[b]?a>b:s2[a]<s2[b];
	});
	for(int len=1; len<n2; len*=2) {
		memcpy(cl2, cl, 4*n2);
		memcpy(sa2, sa, 4*n2);
		for(int i=0; i<n2; ++i) {
			cl[sa[i]]=i>0&&cl2[sa[i-1]]==cl2[sa[i]]&&sa[i-1]+len<n2&&cl2[sa[i-1]+len/2]==cl2[sa[i]+len/2]?cl[sa[i-1]]:i;
			cnt[i]=i;
		}
		for(int i1=0, i2=sa2[0]-len; i1<n2; ++i1, i2=sa2[i1]-len)
			if(i2>=0)
				sa[cnt[cl[i2]]++]=i2;
	}
	for(int i=0; i<n2; ++i)
		cl[sa[i]]=i;
	for(int i=0, k=0; i<n2; ++i, k-=k>0) {
		if(cl[i]>=n2-1)
			continue;
		for(int j=sa[cl[i]+1]; max(i, j)+k<n2&&s2[i+k]==s2[j+k]; ++k);
		lcp[cl[i]]=k;
	}
	long long *ans = new long long[n];
	for(int i=0; i<n; ++i)
		ans[i]=(long long)s[i].size()*(s[i].size()+1)/2;
	int *qu = new int[n2], qh=0, qt=0;
	for(int i1=0, i2=0; i1<n2; ++i1) {
		while(i2<n2-1&&(pofs[sa[i2]]==-1||pofs[sa[i2]]==pofs[sa[i1]])) {
			while(qt>qh&&lcp[i2]<=lcp[qu[qt-1]])
				--qt;
			qu[qt++]=i2++;
		}
		if(pofs[sa[i1]]!=-1)
			ans[pofs[sa[i1]]]-=max(i1>0?lcp[i1-1]:0, qh==qt?0:lcp[qu[qh]]);
		if(qu[qh]==i1)
			++qh;
	}
	for(int i=0; i<n; ++i)
		cout << ans[i] << "\n";
}
=
