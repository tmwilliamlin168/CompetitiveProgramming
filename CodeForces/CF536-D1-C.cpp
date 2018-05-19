/*
	- WLOG we can fix R to be a certain value, say 1
		- Because if person i is the minimum for some (S, R), person i will also be the minimum for (S*k, R*k)
	- Then the problem becomes to find all i such that S/si+1/ri is minimum for some x>0
	- Replace S with x and you can use convex hull trick
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=2e5;
int n, qt;
ll a[mxN], b[mxN];
vector<int> c[mxN], ans;

struct tr {
	int fi, se, i;
	inline bool operator<(const tr &o) const {
		return fi==o.fi?se>o.se:fi<o.fi;
	}
} trs[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> trs[i].fi >> trs[i].se, trs[i].i=i;
	sort(trs, trs+n);
	for(int i=0; i<n; ++i) {
		if(i&&trs[i].fi==a[qt-1]) {
			if(trs[i].se==b[qt-1])
				c[qt-1].push_back(trs[i].i);
			continue;
		}
		while((qt>=1&&trs[i].se>=b[qt-1])||
				(qt>=2&&a[qt-2]*trs[i].se*(b[qt-2]-b[qt-1])*(trs[i].fi-a[qt-1])>trs[i].fi*b[qt-2]*(b[qt-1]-trs[i].se)*(a[qt-1]-a[qt-2])))
			c[--qt].clear();
		a[qt]=trs[i].fi, b[qt]=trs[i].se;
		c[qt].push_back(trs[i].i);
		++qt;
	}
	for(int i=0; i<qt; ++i)
		for(int ci : c[i])
			ans.push_back(ci);
	sort(ans.begin(), ans.end());
	for(int ai : ans)
		cout << ai+1 << " ";
}
