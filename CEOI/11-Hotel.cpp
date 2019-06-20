#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, m, o, c[mxN], p[mxN], p2[mxN], a[mxN];
vector<int> va[mxN], vb[mxN+1];
priority_queue<int> pq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> o;
	for(int i=0; i<n; ++i)
		cin >> c[i] >> p[i];
	memcpy(p2, p, 4*n);
	sort(p2, p2+n);
	for(int i=0; i<n; ++i) {
		p[i]=lower_bound(p2, p2+n, p[i])-p2;
		va[p[i]].push_back(c[i]);
	}
	for(int i=0, d, v; i<m; ++i) {
		cin >> d >> v;
		vb[lower_bound(p2, p2+n, v)-p2].push_back(d);
	}
	for(int i=0; i<n; ++i)
		sort(va[i].begin(), va[i].end());
	for(int i=0, k=0; i<n; ++i) {
		for(int b : vb[i])
			pq.push(b);
		for(int j=0; j<va[i].size()&&pq.size()&&pq.top()>va[i][j]; ++j) {
			a[k++]=pq.top()-va[i][j];
			pq.pop();
		}
	}
	nth_element(a, a+o, a+min(n, m), greater<int>());
	cout << accumulate(a, a+o, 0ll);
}
