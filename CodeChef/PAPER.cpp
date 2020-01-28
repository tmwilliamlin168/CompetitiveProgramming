#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

int t, n, m;
ll w1, h1, w2, h2;
string s;

void solve() {
	cin >> n >> m >> w2 >> h2 >> s;
	w1=0, h1=0;
	vector<ar<ll, 2>> a;
	for(int i=0, x, y; i<m; ++i) {
		cin >> x >> y;
		a.push_back({x, y});
	}
	int c=0;
	for(int i=0; i<n&&c<2; ++i) {
		if(s[i]=='U'||s[i]=='D')
			continue;
		if(s[i]=='L') {
			int m=a.size();
			for(int j=0; j<m; ++j)
				a.push_back({w1-(a[j][0]-w1), a[j][1]});
			w1=w1-(w2-w1);
		} else {
			int m=a.size();
			for(int j=0; j<m; ++j)
				a.push_back({w2+(w2-a[j][0]), a[j][1]});
			w2=w2+(w2-w1);
		}
		++c;
	}
	c=0;
	for(int i=0; i<n&&c<2; ++i) {
		if(s[i]=='L'||s[i]=='R')
			continue;
		if(s[i]=='D') {
			int m=a.size();
			for(int j=0; j<m; ++j)
				a.push_back({a[j][0], h1-(a[j][1]-h1)});
			h1=h1-(h2-h1);
		} else {
			int m=a.size();
			for(int j=0; j<m; ++j)
				a.push_back({a[j][0], h2+(h2-a[j][1])});
			h2=h2+(h2-h1);
		}
		++c;
	}
	sort(a.begin(), a.end(), [](const ar<ll, 2> &i, const ar<ll, 2> &j) {
		return i[1]^j[1]?i[1]<j[1]:i[0]<j[0];
	});
	double md=1e18;
	set<ar<ll, 2>> s;
	for(int i=0; i<a.size(); ++i) {
		auto it1=s.insert(a[i]).first, it2=it1;
		for(int j=0; j<3&&++it1!=s.end(); ) {
			if(a[i][1]-(*it1)[1]>=md) {
				it1=--s.erase(it1);
				continue;
			}
			md=min(hypot(a[i][0]-(*it1)[0], a[i][1]-(*it1)[1]), md);
			++j;
		}
		for(int j=0; j<3&&it2!=s.begin(); ) {
			if(a[i][1]-(*--it2)[1]>=md) {
				it2=s.erase(it2);
				continue;
			}
			md=min(hypot(a[i][0]-(*it2)[0], a[i][1]-(*it2)[1]), md);
			++j;
		}
	}
	cout << md << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cout << fixed << setprecision(9);
	cin >> t;
	while(t--)
		solve();
}
