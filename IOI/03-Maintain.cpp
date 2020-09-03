#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=200;
int n, w, p[mxN];
vector<ar<int, 3>> e;

int find(int x) {
	return x^p[x]?p[x]=find(p[x]):x;
}

bool join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return 0;
	p[x]=y;
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> w;
	for(int a, b, c; w--; ) {
		cin >> a >> b >> c, --a, --b;
		e.push_back({c, a, b});
		sort(e.begin(), e.end());
		vector<ar<int, 3>> e2;
		int ans=0;
		iota(p, p+n, 0);
		for(auto a : e) {
			if(join(a[1], a[2])) {
				ans+=a[0];
				e2.push_back(a);
			}
		}
		e=e2;
		cout << (e.size()<n-1?-1:ans) << endl;
	}
}
