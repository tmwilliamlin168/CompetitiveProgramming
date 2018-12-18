#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream cin("mixmilk.in");
	ofstream cout("mixmilk.out");
	
	//input
	int c[3], m[3];
	for(int i=0; i<3; ++i)
		cin >> c[i] >> m[i];
	//Do the 100 pours
	for(int it=0; it<100; ++it) {
		int from=it%3, to=(it+1)%3;
		int amount=m[from];
		//Make sure milk doesn't overflow
		amount=min(c[to]-m[to], amount);
		m[from]-=amount;
		m[to]+=amount;
	}
	//output
	for(int i=0; i<3; ++i)
		cout << m[i] << "\n";
}
