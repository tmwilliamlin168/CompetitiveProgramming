#include <bits/stdc++.h>
using namespace std;

string s;
int a[500001], b, c;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> s;
	for(int i=0; i<s.size(); ++i) {
		a[i]+=(s[s.size()-1-i]-'0')*9;
		a[i+1]=a[i]/10;
		a[i]%=10;
		b+=a[i];
	}
	b+=a[s.size()];
	for(; b>c; ++c) {
		for(int i=0; ; ++i) {
			if(a[i]>8) {
				a[i]=0;
				b-=9;
			} else {
				++a[i];
				++b;
				break;
			}
		}
	}
	cout << (c+8)/9;
}
