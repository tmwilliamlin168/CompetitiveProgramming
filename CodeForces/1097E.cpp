#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int t, n, a[mxN+1], p[mxN+1];
bool u[mxN+1];
array<int, 2> ft[mxN+1];

void upd(int i, array<int, 2> x) {
	for(; i<=n; i+=i&-i)
		ft[i]=max(x ,ft[i]);
}

array<int, 2> qry(int i) {
	array<int, 2> r{};
	for(; i; i-=i&-i)
		r=max(ft[i], r);
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> n;
		for(int i=1; i<=n; ++i)
			cin >> a[i];
		memset(u+1, 0, n);
		int nl=n;
		vector<vector<int>> ans;
		while(nl) {
			memset(ft+1, 0, sizeof(ft[1])*n);
			for(int i=1; i<=n; ++i) {
				if(u[i])
					continue;
				array<int, 2> b=qry(a[i]);
				upd(a[i], {b[0]+1, i});
				p[i]=b[1];
			}
			array<int, 2> b=qry(n);
			if((long long)b[0]*(b[0]+1)/2<=nl)
				break;
			ans.push_back({});
			for(int i=b[1]; i; i=p[i], --nl) { 
				u[i]=1;
				ans.back().push_back(a[i]);
			}
			reverse(ans.back().begin(), ans.back().end());
		}
		while(nl) {
			ans.push_back({});
			for(int i=1; i<=n; ++i) {
				if(u[i]||ans.back().size()&&ans.back().back()<a[i])
					continue;
				ans.back().push_back(a[i]);
				u[i]=1;
				--nl;
			}
		}
		cout << ans.size();
		for(vector<int> v : ans) {
			cout << "\n" << v.size();
			for(int b : v)
				cout << " " << b;
		}
		cout << "\n";
	}
}
