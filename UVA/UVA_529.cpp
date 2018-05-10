/*
	- Iterative dfs with optimizations
		- Return if the last number is greater
		- Return if the last number is too small to become the given number in the remaining number of steps
*/

#include <bits/stdc++.h>
using namespace std;

int n, ans1, ans2[24], tmp[24]={1, 2};

void dfs(int d) {
	if(ans2[0])
		return;
	int n2=tmp[d-1];
	if(n2==n)
		memcpy(ans2, tmp, sizeof(ans2));
	else {
		if(d>=ans1||n2>n)
			return;
		for(int i=0; i<ans1-d; ++i)
			n2*=2;
		if(n2<n)
			return;
		for(int i=d-1; i>=0; --i) {
			for(int j=d-1; j>=i&&tmp[i]+tmp[j]>tmp[d-1]; --j) {
				tmp[d]=tmp[i]+tmp[j];
				dfs(d+1);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(1) {
		cin >> n;
		if(!n)
			break;
		ans2[0]=0;
		for(ans1=1; !ans2[0]; ++ans1)
			dfs(1);
		cout << ans2[0];
		for(int i=1; i<ans1-1; ++i)
			cout << " " << ans2[i];
		cout << "\n";
	}
}
