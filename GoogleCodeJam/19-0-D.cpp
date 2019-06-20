#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t, n, b, f;
	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> n >> b >> f;
		vector<int> v{b};
		for(int bs=16, pb=1024; bs; pb=bs, bs/=2) {
			string s(1024, '0'), t;
			for(int i=1; i*bs<1024; i+=2)
				for(int j=i*bs; j<(i+1)*bs; ++j)
					s[j]='1';
			cout << s.substr(0, n) << endl;
			cin >> t;
			for(int i=n; i<1024; ++i)
				t+=s[i];
			vector<int> w;
			for(int i1=0, i2=0, j=0; i1<1024/pb; ++i1, i2=j) {
				if(pb<1024) {
					for(int k : {0, 1}) {
						w.push_back(bs);
						for(; j<i2+pb-v[i1]&&t[j]=='0'+k; --w.back(), ++j);
					}
				} else {
					for(int k=j; k<i2+pb-v[i1]; j=k) {
						for(; k<i2+pb-v[i1]&&t[k]==t[j]; ++k);
						w.push_back(bs-(k-j));
					}
				}
			}
			v=w;
		}
		for(int i=0; i<n; ++i)
			if(v[i])
				cout << i << " ";
		cout << endl;
		cin >> n;
	}
}
