#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=2e5;
int n, k, d[mxN], b[mxN];
ar<int, 4> a[mxN], p[4];
ar<int, 4> ir{1, 1, INT_MAX, INT_MAX};
vector<int> v1, v2;

ar<int, 4> it(ar<int, 4> a, ar<int, 4> b) {
	return {max(a[0], b[0]), max(a[1], b[1]), min(a[2], b[2]), min(a[3], b[3])};
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
		v2.push_back(i);
	}
	while(1) {
		vector<int> u=v2;
		v2.clear();
		for(int i=0; i<k; ++i)
			p[i]=ir;
		for(int i=0; i<n; ++i) {
			bool ok=0;
			for(int j=0; j<k; ++j) {
				ar<int, 4> bl=it(p[j], a[u[i]]);
				if(bl[0]<=bl[2]&&bl[1]<=bl[3]) {
					p[j]=bl;
					v1.push_back(u[i]);
					ok=1;
					break;
				}
			}
			if(!ok)
				v2.push_back(u[i]);
		}
		if(v2.empty()) {
			for(int j=0; j<k; ++j)
				cout << p[j][0] << " " << p[j][1] << "\n";
			break;
		}
		random_shuffle(v2.begin(), v2.end());
		v2.insert(v2.end(), v1.begin(), v1.end());
		v1.clear();
	}
}
