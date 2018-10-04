#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	int *a = new int[n];
	unordered_map<int, int> p[5];
	for(int k=0; k<5; ++k) {
		for(int i=0; i<n; ++i) {
			int ai;
			cin >> ai;
			p[k][ai]=i;
			if(!k)
				a[i]=ai;
		}
	}
	sort(a, a+n, [&p](const int &a, const int &b) {
		int c=0;
		for(int k=0; k<5; ++k)
			c+=p[k][a]>p[k][b]?1:-1;
		return c<0;
	});
	for(int i=0; i<n; ++i)
		cout << a[i] << "\n";
}
