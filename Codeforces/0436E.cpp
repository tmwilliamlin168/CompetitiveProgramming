/*
	- Sort elements by b-a decreasing
	- Start with the best solution with the first ceil(w/2) elements
	- Repeatedly update solution when new elements are added in order
*/

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int mxN=3e5;
int n, w, a[mxN], b[mxN], p[mxN];
long long ans;
string s;
set<pair<int, int>, greater<pair<int, int>>> s1, s2;

inline void rem1(int i) {
	if(s[i]=='1') {
		ans-=a[i];
		s1.erase({a[i], i});
		s[i]='0';
	} else {
		ans-=b[i]-a[i];
		s1.erase({b[i]-a[i], i});
		s2.erase({b[i], i});
		s1.insert({a[i], i});
		s[i]='1';
	}
}

inline void add2(int i) {
	ans+=b[i];
	s1.insert({b[i]-a[i], i});
	s2.insert({b[i], i});
	s[i]='2';
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> w;
	for(int i=0; i<n; ++i) {
		cin >> a[i] >> b[i];
		s+='0';
		p[i]=i;
	}
	sort(p, p+n, [&](const int &i, const int &j) {
		return b[i]-a[i]>b[j]-a[j];
	});
	for(int i=0; i<(w+1)/2; ++i)
		add2(p[i]);
	if(w&1)
		rem1(p[0]);
	for(int i=(w+1)/2; i<n; ++i) {
		int a1=s1.begin()->fi-a[p[i]], a2=s1.size()>=2?s1.begin()->fi+(++s1.begin())->fi-b[p[i]]:0, a3=s2.size()>=1?s2.begin()->fi-b[p[i]]:0;
		if(a1>0&&a1>a2&&a1>a3) {
			ans+=a[p[i]];
			rem1(s1.begin()->se);
			s[p[i]]='1';
			s1.insert({a[p[i]], p[i]});
		} else if(a2>0&&a2>a3) {
			int j1=s1.begin()->se, j2=(++s1.begin())->se;
			rem1(j1);
			rem1(j2);
			add2(p[i]);
		} else if(a3>0) {
			int j=s2.begin()->se;
			rem1(j);
			rem1(j);
			add2(p[i]);
		}
	}
	cout << ans << "\n" << s;
}
