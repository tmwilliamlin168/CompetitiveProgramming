#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	auto f=[](vector<int> a, vector<int> b) {
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		array<int, 2> r{};
		for(int i1=0, i2=0; i1<a.size(); ++i1) {
			while(b[i2]<a[i1])
				++i2;
			r=max(array<int, 2>{i1+b.size()-i2, -a[i1]}, r);
		}
		return -r[1];
	};
	int t, p, q;
	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> p >> q;
		vector<int> vn{0}, vs{q+1}, ve{0}, vw{q+1};
		for(int xi, yi; p--; ) {
			char ci;
			cin >> xi >> yi >> ci;
			if(ci=='N')
				vn.push_back(yi+1);
			else if(ci=='S')
				vs.push_back(yi-1);
			else if(ci=='E')
				ve.push_back(xi+1);
			else
				vw.push_back(xi-1);
		}
		cout << "Case #" << ti << ": " << f(ve, vw) << " " << f(vn, vs) << "\n";
	}
}
