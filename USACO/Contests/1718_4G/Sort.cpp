#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n;
array<int, 2> a[mxN];
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	ifstream cin("sort.in");
	ofstream cout("sort.out");
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0];
		a[i][1]=i;
	}
	sort(a, a+n);
	for(int i=0; i<n; ++i) {
		pq.push(a[i][1]);
		if(pq.top()<=i)
			pq.pop();
	}
	cout << max((int)pq.size(), 1);
}
