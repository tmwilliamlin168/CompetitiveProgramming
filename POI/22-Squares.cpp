/*
	- We can prove with brute force that for large enough n, (sum(1..n, i^2), sum(1..n+1, i^2)] has exactly 31 overgrown integers
	- We just have to run the simple dp for small cases
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int S=651;
int dp[S];
ll n, lb=1, rb=2e6, a;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	memset(dp, 1, 4*S);
	dp[0]=0;
	for(int i=1; i<14; ++i)
		for(int j=i*i; j<S; ++j)
			if(dp[j]>i&&dp[j-i*i]<i)
				dp[j]=i;
	cin >> n;
	for(int i=S-1, mn=INT_MAX; i; --i) {
		if(i<=n)
			a+=dp[i]>mn;
		mn=min(dp[i], mn);
	}
	if(n<S) {
		if(dp[n]>13)
			cout << "-";
		else
			cout << dp[n];
		cout << " " << a;
		return 0;
	}
	while(lb<rb) {
		ll mb=(lb+rb)/2;
		if(mb*(mb+1)*(2*mb+1)/6>=n)
			rb=mb;
		else
			lb=mb+1;
	}
	ll b=lb*(lb+1)*(2*lb+1)/6-n;
	cout << lb+(b<144&&dp[S-1-b]==13) << " ";
	a+=(lb-12)*31;
	for(int i=S; i>S-min(144ll, b); --i)
		a-=dp[i-1]==13;
	cout << a;
}
