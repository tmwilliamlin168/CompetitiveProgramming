#include <bits/stdc++.h>
using namespace std;

#define ll unsigned long long

const ll base=1e6+3;
ll n, ans;
unordered_map<ll, int> cnt[6];

int main() {
	ifstream cin("cowpatibility.in");
	ofstream cout("cowpatibility.out");
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		int b[5];
		for(int j=0; j<5; ++j)
			cin >> b[j];
		sort(b, b+5);
		//Iterate over all subsets
		for(int j=1; j<32; ++j) {
			int c=__builtin_popcount(j);
			//pray to cow gods for no collisions
			ll hash=0;
			for(int k=0; k<5; ++k)
				if(j>>k&1)
					hash=hash*base+b[k];
			//add for odd-sized subsets and subtract for even-sized
			ans+=cnt[c][hash]*(c&1?1:-1);
			++cnt[c][hash];
		}
	}
	//we found number of compatible, now take the complement
	cout << n*(n-1)/2-ans;
}
