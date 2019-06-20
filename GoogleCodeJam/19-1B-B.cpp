#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, w, a[6];
	cin >> t >> w;
	for(long long n; t--; ) {
		cout << 224 << endl;
		cin >> n;
		a[3]=n>>56;
		a[4]=n>>44&127;
		a[5]=n>>37&127;
		cout << 56 << endl;
		cin >> n;
		n-=a[3]<<14;
		n-=a[4]<<11;
		n-=a[5]<<9;
		a[0]=n>>56;
		a[1]=n>>28&127;
		a[2]=n>>18&127;
		for(int i=0; i<6; ++i)
			cout << a[i] << " ";
		cout << endl;
		cin >> n;
	}
}
