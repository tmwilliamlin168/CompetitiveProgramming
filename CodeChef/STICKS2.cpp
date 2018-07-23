#include <bits/stdc++.h>
using namespace std;
 
#define pii pair<int, int>
#define fi first
#define se second
 
int t, n, k;
map<int, int> mp;
 
inline void solve() {
	mp.clear();
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		int ai;
		cin >> ai;
		++mp[ai];
	}
	pii a;
	for(auto it=mp.begin(); it!=mp.end(); ++it)
		a=max(pii(it->se, it->fi), a);
	int k2=k-(int)mp.size();
	if(k-min(a.fi, 3)-((int)mp.size()-1)<=0) {
		cout << "-1\n";
		return;
	}
	for(auto it=mp.begin(); it!=mp.end(); ++it)
		--it->se;
	long long ans=LLONG_MAX, m1=0;
	for(auto it=mp.begin(); it!=mp.end()&&k2>0; ++it) {
		if(!it->se)
			continue;
		if(it->se>=3&&k2<=it->se)
			ans=min((long long)it->fi*it->fi, ans);
		k2-=it->se;
		it->se=0;
		if(k2<=1) {
			for(auto it2=it; it2!=mp.end(); ++it2)
				if(it2->se>=1)
					ans=min((long long)it->fi*it2->fi, ans);
		} else if(k2<=2) {
			for(auto it2=it; it2!=mp.end(); ++it2)
				if(it2->se>=2)
					ans=min((long long)it->fi*it2->fi, ans);
		}
		m1=it->fi;
	}
	cout << ans << "\n";
}
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
} 
