#include <bits/stdc++.h>
using namespace std;

long long l, r;
int al[19], ar[19], c[10];

bool e(int i=0, bool b1=0, bool b2=0) {
	if(b1&&b2)
		return 1;
	if(i>18)
		return 1;
	for(int j=0; j<10; ++j) {
		if(!c[j]||!b1&&j<al[i]||!b2&&j>ar[i])
			continue;
		--c[j];
		bool b3=e(i+1, b1||j>al[i], b2||j<ar[i]);
		++c[j];
		if(b3)
			return 1;
	}
	return 0;
}

int a(int i=0, int b=0) {
	if(i>18)
		return e();
	int d=0;
	for(; b<10; ++b) {
		++c[b];
		d+=a(i+1, b);
		--c[b];
	}
	return d;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> l >> r;
	for(int i=18; i>=0; --i, l/=10)
		al[i]=l%10;
	for(int i=18; i>=0; --i, r/=10)
		ar[i]=r%10;
	cout << a();
}
