#include <bits/stdc++.h>
using namespace std;

#define MAX 100001

int main() {
	int n, m;
	cin >> n >> m;
	int a[n+1]; a[0] = 0;
	for (int i = 1; i <= n; i++) cin >> a[i];
	set <int> s[MAX];
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		if (a[x] != a[y]) {
			s[a[x]].insert(a[y]);
			s[a[y]].insert(a[x]);
		}
	}
	int max_val = -MAX;
	int color = 1;
	sort(a+1, a+n+1);
	for (int i = 1; i <= n; i++) {
		if ((int)s[a[i]].size() > max_val) {
			color = a[i]; max_val = (int)s[a[i]].size();	
		}
	}
	cout << color << endl;
	return 0;
}
