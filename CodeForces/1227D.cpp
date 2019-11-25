#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int mxN=2e5;
int n, a[mxN], m, ans[mxN];
array<int, 2> b[mxN];
vector<array<int, 2>> c[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		b[i]={-a[i], i};
	}
	sort(b, b+n);
	cin >> m;
	for(int i=0, k, p; i<m; ++i) {
		cin >> k >> p, --k, --p;
		c[k].push_back({p, i});
	}
	oset<int> s;
	for(int i=0; i<n; ++i) {
		s.insert(b[i][1]);
		for(array<int, 2> d : c[i])
			ans[d[1]]=a[*s.find_by_order(d[0])];
	}
	for(int i=0; i<m; ++i)
		cout << ans[i] << "\n";
}
