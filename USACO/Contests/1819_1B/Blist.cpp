#include <bits/stdc++.h>
using namespace std;

int n, a[1001], si, ti, bi, ans;

int main() {
	ifstream cin("blist.in");
	ofstream cout("blist.out");
	
	//input
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> si >> ti >> bi;
		//add bi to all moments of time [si, ti]
		for(int j=si; j<=ti; ++j)
			a[j]+=bi;
	}
	//answer is maximum of all moments
	for(int i=1; i<=1000; ++i)
		ans=max(a[i], ans);
	//output
	cout << ans;
}
