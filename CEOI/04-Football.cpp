/*
	- https://en.wikipedia.org/wiki/Round-robin_tournament#Scheduling_algorithm
	- Team 1 will alternate color
	- Try to make other teams alternate whenever possible, only 2 teams should stay every other transition
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	cout << n-2 << "\n";
	for(int i=0; i<n-1; ++i) {
		if(i&1)
			cout << i+1 << " " << n;
		else
			cout << n << " " << i+1;
		for(int j=1; j<n/2; ++j) {
			if(j&1)
				cout << " " << (i-j+n-1)%(n-1)+1 << " " << (i+j)%(n-1)+1;
			else
				cout << " " << (i+j)%(n-1)+1 << " " << (i-j+n-1)%(n-1)+1;
		}
		cout << "\n";
	}
}
