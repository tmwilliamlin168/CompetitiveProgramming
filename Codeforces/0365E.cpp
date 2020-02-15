/*
	- Only 5000 possible inputs, so just test them locally (because it is hard to prove that a solution works)
	- This solution iterates over the number of prime factors to use
	- It then constructs all numbers <=2n^2 with these prime factors
	- The larger numbers have more prime factors, so if we create over n numbers, we choose the n largest ones
*/

#include <bits/stdc++.h>
using namespace std;

const int primes[]={2, 3, 5, 7, 11};
int n;
vector<int> ans={1};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; ; ++i) {
		for(int j=0; j<ans.size(); ++j)
			if(ans[j]*primes[i]<=2*n*n)
				ans.push_back(ans[j]*primes[i]);
		if(ans.size()>=n)
			break;
	}
	for(int i=0; i<n; ++i)
		cout << ans[ans.size()-i-1] << " ";
}
