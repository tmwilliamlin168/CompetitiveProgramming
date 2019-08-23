#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, a[mxN], b[mxN];
priority_queue<array<int, 2>> pq;
long long ans;

void fk() {
	cout << -1;
	exit(0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n; ++i) {
		cin >> b[i];
		pq.push({b[i], i});
	}
	while(pq.size()) {
		int i=pq.top()[1], c=b[(i+1)%n]+b[(i+n-1)%n], t=(b[i]-a[i])/c;
		pq.pop();
		if(a[i]==b[i])
			continue;
		if(t<=0)
			fk();
		b[i]-=t*c;
		pq.push({b[i], i});
		ans+=t;
	}
	cout << ans;
}
