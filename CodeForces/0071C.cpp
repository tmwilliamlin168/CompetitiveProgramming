#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[mxN];

void chk(int x) { //x = side length
	//iterate starting index
	for(int si=0; si<x; ++si) {
		bool ok=1;
		for(int j=si; j<n&&ok; j+=x)
			ok=a[j];
		if(ok) {
			cout << "YES";
			exit(0);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	//iterate through divisors of n
	//O(sqrt(n)) iterations, O(n) check, so O(nsqrt(n)) overall
	for(int i=1; i*i<=n; ++i) {
		if(n%i) //side length must divide n
			continue;
		if(n/i>=3) //number of points must be >= 3 to form a nondegenerate polygon
			chk(i);
		if(i>=3)
			chk(n/i); //if i = sqrt(n) then this will check x = sqrt(n) again, but we don't care since checking again doesn't do anything
	}
	cout << "NO";
}
